// Copyright (C) Intel Corp.  2018.  All Rights Reserved.

// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:

// The above copyright notice and this permission notice (including the
// next paragraph) shall be included in all copies or substantial
// portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

//  **********************************************************************/
//  * Authors:
//  *   Mark Janes <mark.a.janes@intel.com>
//  **********************************************************************/

#include "glframe_metrics_amd_gpa.hpp"

#include <GL/gl.h>
#include <GL/glext.h>

#include <string>
#include <vector>

#include "glretrace.hpp"

#include "GPUPerfAPI.h"
#include "GPUPerfAPIFunctionTypes.h"

#include "glframe_traits.hpp"

using glretrace::MetricId;
using glretrace::OnFrameRetrace;
using glretrace::RenderId;
using glretrace::PerfMetricsAMDGPA;
using glretrace::PerfContext;
using glretrace::NoAssign;
using glretrace::NoCopy;

struct MetricDescription {
  MetricId id;
  std::string name;
  std::string description;
  MetricDescription() {}
  MetricDescription(MetricId i,
                    const std::string &n,
                    const std::string &d)
      : id(i), name(n), description(d) {}
};

class PerfMetric: public NoCopy, NoAssign {
 public:
  explicit PerfMetric(int index);
  MetricId id() const;
  const std::string &name() const;
  const std::string &description() const;
  float getMetric(const std::vector<unsigned char> &data) const;
 private:
  const int m_index;
  std::string m_name, m_description;
  GPA_Type m_type;
};

class PerfGroup : public NoCopy, NoAssign {
 public:
  explicit PerfGroup(int metric_index);
  ~PerfGroup();
  int metricCount() const { return m_metrics.size(); }
  void metrics(std::vector<MetricDescription> *m) const;
  void begin(RenderId render);
  void end(RenderId render);
  // void publish(MetricId metric, PerfMetricsIntel::MetricMap *m);
 private:
  std::vector<PerfMetric *> m_metrics;
};

namespace glretrace {

class PerfContext : public NoCopy, NoAssign {
 public:
  explicit PerfContext(OnFrameRetrace *cb);
  ~PerfContext();
  int groupCount() const;
  void selectMetric(MetricId metric);
  void selectGroup(int index);
  void begin(RenderId render);
  void end();
  // void publish(MetricMap *metrics);
 private:
  std::vector<PerfGroup*> m_groups;
};
}  // namespace glretrace

PerfMetric::PerfMetric(int index) : m_index(index) {
  const char *name, *description;
  GPA_Status ok = GPA_GetCounterName(index, &name);
  assert(ok = GPA_STATUS_OK);
  m_name = name;
  ok = GPA_GetCounterDescription(index, &description);
  assert(ok = GPA_STATUS_OK);
  m_description = description;
  ok = GPA_GetCounterDataType(index, &m_type);
  printf("new metric: %s : %s\n", name, description);
}

PerfGroup::PerfGroup(int metric_index) {
  gpa_uint32 max_count;
  GPA_GetNumCounters(&max_count);
  GPA_Status ok;
  while (metric_index < max_count) {
    ok = GPA_EnableCounter(metric_index);
    assert(ok = GPA_STATUS_OK);
    gpa_uint32 passes;
    ok = GPA_GetPassCount(&passes);
    assert(ok = GPA_STATUS_OK);
    assert(passes > 0);
    if (passes > 1)
      break;
    m_metrics.push_back(new PerfMetric(metric_index));
    ++metric_index;
  }
  ok = GPA_DisableAllCounters();
  assert(ok = GPA_STATUS_OK);
}

PerfContext::PerfContext(OnFrameRetrace *cb) {
  gpa_uint32 count;
  GPA_Status ok = GPA_GetNumCounters(&count);
  assert(ok = GPA_STATUS_OK);
  ok = GPA_DisableAllCounters();
  assert(ok = GPA_STATUS_OK);

  int index = 0;
  while (index < count) {
    printf("new group\n");
    m_groups.push_back(new PerfGroup(index));
    index += m_groups.back()->metricCount();
  }
}

PerfMetricsAMDGPA::PerfMetricsAMDGPA(OnFrameRetrace *cb) {
  GPA_Initialize();
  Context *c = getCurrentContext();
  GPA_OpenContext(c);
  GPA_SelectContext(c);

  m_contexts[c] = new PerfContext(cb);
}

PerfMetricsAMDGPA::~PerfMetricsAMDGPA() {
  GPA_Destroy();
}

int PerfMetricsAMDGPA::groupCount() const { return 0; }
void PerfMetricsAMDGPA::selectMetric(MetricId metric) {}
void PerfMetricsAMDGPA::selectGroup(int index) {}
void PerfMetricsAMDGPA::begin(RenderId render) {}
void PerfMetricsAMDGPA::end() {}
void PerfMetricsAMDGPA::publish(ExperimentId experimentCount,
               SelectionId selectionCount,
               OnFrameRetrace *callback) {}

void PerfMetricsAMDGPA::endContext() {
  // close all open queries
}

void PerfMetricsAMDGPA::beginContext() {
  Context *c = getCurrentContext();
  if (m_contexts.find(c) == m_contexts.end()) {
    GPA_OpenContext(c);
    m_contexts[c] = new PerfContext(NULL);
  }
  GPA_SelectContext(c);
  m_current_context = m_contexts[c];
}
