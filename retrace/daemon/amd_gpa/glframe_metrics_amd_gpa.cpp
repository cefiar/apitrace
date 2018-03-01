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
using glretrace::ID_PREFIX_MASK;

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
  explicit PerfMetric(int group, int index);
  MetricId id() const;
  const std::string &name() const { return m_name; }
  const std::string &description() const { return m_description; }
  float getMetric(const std::vector<unsigned char> &data) const;
  void enable();
 private:
  const int m_group, m_index;
  std::string m_name, m_description;
  GPA_Type m_type;
};

class PerfGroup : public NoCopy, NoAssign {
 public:
  PerfGroup(int group_index, int metric_index);
  ~PerfGroup();
  int nextMetricIndex() const { return m_next_metric; }
  void metrics(std::vector<MetricDescription> *m) const;
  void begin(RenderId render);
  void end(RenderId render);
  void selectMetric(MetricId metric);
  void selectAll();
  // void publish(MetricId metric, PerfMetricsIntel::MetricMap *m);
 private:
  int m_next_metric;
  std::vector<PerfMetric *> m_metrics;
};

namespace glretrace {

class PerfContext : public NoCopy, NoAssign {
 public:
  explicit PerfContext(OnFrameRetrace *cb);
  ~PerfContext();
  int groupCount() const { return m_groups.size(); }
  void selectMetric(MetricId metric);
  void selectGroup(int index);
  void begin(RenderId render);
  void end();
  // void publish(MetricMap *metrics);
 private:
  std::vector<PerfGroup*> m_groups;
};
}  // namespace glretrace

PerfMetric::PerfMetric(int group, int index) : m_group(group),
                                               m_index(index) {
  const char *name, *description;
  GPA_Status ok = GPA_GetCounterName(index, &name);
  assert(ok == GPA_STATUS_OK);
  m_name = name;
  ok = GPA_GetCounterDescription(index, &description);
  assert(ok == GPA_STATUS_OK);
  m_description = description;
  ok = GPA_GetCounterDataType(index, &m_type);
}

MetricId
PerfMetric::id() const {
  return MetricId(m_group, m_index);
}

void PerfMetric::enable() {
  GPA_Status ok = GPA_EnableCounter(m_index);
  assert(ok == GPA_STATUS_OK);
}


PerfGroup::PerfGroup(int group_index, int metric_index) {
  m_next_metric = metric_index;
  gpa_uint32 max_count;
  GPA_Status ok =  GPA_GetNumCounters(&max_count);
  assert(ok == GPA_STATUS_OK);
  while (m_next_metric < max_count) {
    ok = GPA_EnableCounter(m_next_metric);
    assert(ok == GPA_STATUS_OK);
    gpa_uint32 passes;
    ok = GPA_GetPassCount(&passes);
    assert(ok == GPA_STATUS_OK);
    assert(passes > 0);
    if (passes > 1) {
      if (m_metrics.empty()) {
        // single metric requires 2 passes.  Skip it.
        ok = GPA_DisableAllCounters();
        assert(ok == GPA_STATUS_OK);
        ++m_next_metric;
        continue;
      }
      break;
    }
    m_metrics.push_back(new PerfMetric(group_index, m_next_metric));
    ++m_next_metric;
  }
  ok = GPA_DisableAllCounters();
  assert(ok == GPA_STATUS_OK);
}

void
PerfGroup::metrics(std::vector<MetricDescription> *out) const {
  for (auto m : m_metrics)
    out->push_back(MetricDescription(m->id(),
                                     m->name(),
                                     m->description()));
}

void
PerfGroup::selectMetric(MetricId metric) {
  GPA_Status ok = GPA_DisableAllCounters();
  assert(ok == GPA_STATUS_OK);
  m_metrics[metric.counter()]->enable();
}

void PerfGroup::selectAll() {
  GPA_Status ok = GPA_DisableAllCounters();
  assert(ok == GPA_STATUS_OK);
  for (auto m : m_metrics)
    m->enable();
}

PerfContext::PerfContext(OnFrameRetrace *cb) {
  gpa_uint32 count;
  GPA_Status ok = GPA_GetNumCounters(&count);
  assert(ok == GPA_STATUS_OK);
  ok = GPA_DisableAllCounters();
  assert(ok == GPA_STATUS_OK);

  int index = 0;
  std::vector<MetricDescription> metrics;
  while (index < count) {
    PerfGroup *pg = new PerfGroup(m_groups.size(), index);
    m_groups.push_back(pg);
    index = m_groups.back()->nextMetricIndex();
    pg->metrics(&metrics);
  }
  std::vector<MetricId> ids;
  std::vector<std::string> names;
  std::vector<std::string> descriptions;
  for (auto m : metrics) {
    ids.push_back(m.id);
    names.push_back(m.name);
    descriptions.push_back(m.description);
  }
  if (cb)
    cb->onMetricList(ids, names, descriptions);
}

void
PerfContext::selectMetric(MetricId metric) {
  m_groups[metric.group()]->selectMetric(metric);
}

void
PerfContext::selectGroup(int index) {
  m_groups[index]->selectAll();
}

void gpa_log(GPA_Logging_Type messageType, const char* pMessage) {
  printf("%s\n", pMessage);
}

static const int INVALID_GROUP = -1;

PerfMetricsAMDGPA::PerfMetricsAMDGPA(OnFrameRetrace *cb)
    : m_current_group(INVALID_GROUP) {
  GPA_Status ok;
  ok =  GPA_RegisterLoggingCallback(GPA_LOGGING_ERROR_AND_MESSAGE, gpa_log);
  assert(ok == GPA_STATUS_OK);

  ok = GPA_Initialize();
  assert(ok == GPA_STATUS_OK);
  Context *c = getCurrentContext();
  if (c == NULL)
    c = reinterpret_cast<Context*>(this);
  ok = GPA_OpenContext(c);
  // assert(ok == GPA_STATUS_OK);
  ok = GPA_SelectContext(c);
  assert(ok == GPA_STATUS_OK);

  m_contexts[c] = new PerfContext(cb);
}

PerfMetricsAMDGPA::~PerfMetricsAMDGPA() {
  GPA_Status ok;
  for (auto i : m_contexts) {
    ok = GPA_SelectContext(i.first);
    assert(ok == GPA_STATUS_OK);
    ok =  GPA_CloseContext();
    assert(ok == GPA_STATUS_OK);
  }
  ok = GPA_Destroy();
  assert(ok == GPA_STATUS_OK);
}

int PerfMetricsAMDGPA::groupCount() const {
  return m_contexts.begin()->second->groupCount();
}

void PerfMetricsAMDGPA::selectMetric(MetricId metric) {
  GPA_Status ok = GPA_EndPass();
  //  assert(ok == GPA_STATUS_OK);
  ok = GPA_EndSession();
  // assert(ok == GPA_STATUS_OK);
  m_current_group = INVALID_GROUP;
  for (auto c : m_contexts)
    c.second->selectMetric(metric);
  ok = GPA_BeginSession(&m_session_id);
  assert(ok == GPA_STATUS_OK);
  ok = GPA_BeginPass();
  assert(ok == GPA_STATUS_OK);
}

void PerfMetricsAMDGPA::selectGroup(int index) {
  GPA_Status ok = GPA_EndPass();
  // assert(ok == GPA_STATUS_OK);
  ok = GPA_EndSession();
  // assert(ok == GPA_STATUS_OK);
  m_current_metric = MetricId();  // no metric
  m_current_group = index;
  for (auto c : m_contexts)
    c.second->selectGroup(index);
  ok = GPA_BeginSession(&m_session_id);
  assert(ok == GPA_STATUS_OK);
  ok = GPA_BeginPass();
  assert(ok == GPA_STATUS_OK);
}

void PerfMetricsAMDGPA::begin(RenderId render) {
  GPA_Status ok = GPA_BeginSample(render());
  assert(ok == GPA_STATUS_OK);
  m_open_samples.push_back(render);
}
void PerfMetricsAMDGPA::end() {
  GPA_Status ok = GPA_EndSample();
  assert(ok == GPA_STATUS_OK);
}
void PerfMetricsAMDGPA::publish(ExperimentId experimentCount,
               SelectionId selectionCount,
               OnFrameRetrace *callback) {
}

void
PerfMetricsAMDGPA::endContext() {
  // close all open queries
  GPA_Status ok = GPA_EndSample();
  assert(ok == GPA_STATUS_OK);
}

void
PerfMetricsAMDGPA::beginContext() {
  Context *c = getCurrentContext();
  GPA_Status ok;
  if (m_contexts.find(c) == m_contexts.end()) {
    ok = GPA_OpenContext(c);
    assert(ok == GPA_STATUS_OK);

    PerfContext *pc = new PerfContext(NULL);
    m_contexts[c] = pc;
    if (m_current_group != INVALID_GROUP)
      pc->selectGroup(m_current_group);
    else if (m_current_metric())
      pc->selectMetric(m_current_metric);
  }
  ok = GPA_SelectContext(c);
  assert(ok == GPA_STATUS_OK);
  m_current_context = m_contexts[c];
}
