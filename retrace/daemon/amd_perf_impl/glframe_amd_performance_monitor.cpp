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

#include "glframe_amd_performance_monitor.hpp"

#include <assert.h>
#include <string.h>
#include <float.h>

#include <map>
#include <string>
#include <vector>

#include "glframe_glhelper.hpp"
#include "./gfx_8_0_enum.h"

using glretrace::AMDPerformanceMonitor;
using glretrace::GlFunctions;

struct RegisterConfig {
  uint group;
  uint counter;
  uint type;
  float value;
  RegisterConfig() : group(-1), counter(-1) {}
  explicit RegisterConfig(int c) : group(-1), counter(c) {}
  RegisterConfig(int g, int c) : group(g), counter(c) {}
  RegisterConfig(const RegisterConfig &o)
      : group(o.group), counter(o.counter) {}
  const unsigned char *parse(const unsigned char * buf);
  void select(GLuint monitor, bool enable);
};

const unsigned char *
RegisterConfig::parse(const unsigned char * buf) {
  switch (type) {
    case GL_UNSIGNED_INT64_AMD: {
      value = *reinterpret_cast<const uint64_t*>(buf);
      return buf + sizeof(uint64_t);
    }
    case GL_PERCENTAGE_AMD: {
      value = *reinterpret_cast<const float*>(buf);
      return buf + sizeof(float);
    }
    case GL_UNSIGNED_INT: {
      value = *reinterpret_cast<const uint32_t*>(buf);
      return buf + sizeof(uint32_t);
    }
    case GL_FLOAT: {
      value = *reinterpret_cast<const float*>(buf);
      return buf + sizeof(float);
    }
    default:
      assert(false);
      break;
  }
  return buf;
}

void
RegisterConfig::select(GLuint monitor, bool enable) {
  GlFunctions::SelectPerfMonitorCountersAMD(monitor, enable,
                                            group, 1, &counter);
  assert(!GlFunctions::GetError());
}


RegisterConfig GRBM_GRBM_PERF_SEL_COUNT(GRBM_PERF_SEL_COUNT);
RegisterConfig SPI_SPI_PERF_ES_BUSY(SPI_PERF_ES_BUSY);
RegisterConfig GRBM_GRBM_PERF_SEL_GUI_ACTIVE(GRBM_PERF_SEL_GUI_ACTIVE);
RegisterConfig SPI_SPI_PERF_ES_WAVE(SPI_PERF_ES_WAVE);
RegisterConfig SPI_SPI_PERF_GS_BUSY(SPI_PERF_GS_BUSY);
RegisterConfig SPI_SPI_PERF_GS_WAVE(SPI_PERF_GS_WAVE);
RegisterConfig SPI_SPI_PERF_HS_BUSY(SPI_PERF_HS_BUSY);
RegisterConfig SPI_SPI_PERF_HS_WAVE(SPI_PERF_HS_WAVE);
RegisterConfig SPI_SPI_PERF_LS_BUSY(SPI_PERF_LS_BUSY);
RegisterConfig SPI_SPI_PERF_LS_WAVE(SPI_PERF_LS_WAVE);
RegisterConfig SPI_SPI_PERF_PS_CTL_BUSY(SPI_PERF_PS_CTL_BUSY);
RegisterConfig SPI_SPI_PERF_VS_BUSY(SPI_PERF_VS_BUSY);
RegisterConfig SPI_SPI_PERF_VS_WAVE(SPI_PERF_VS_WAVE);
RegisterConfig VGT_VGT_PERF_VGT_TE11_BUSY(VGT_PERF_VGT_TE11_BUSY);

RegisterConfig PA_SU_PERF_PAPC_PA_INPUT_PRIM(PERF_PAPC_PA_INPUT_PRIM);

std::map<std::string, std::vector<RegisterConfig*>> registers_by_group_name {
  {"GRBM",
    {
      &GRBM_GRBM_PERF_SEL_COUNT,
          &GRBM_GRBM_PERF_SEL_GUI_ACTIVE,
          }
  },
  {"SPI",
    {
      &SPI_SPI_PERF_ES_BUSY,
          &SPI_SPI_PERF_ES_BUSY,
          &SPI_SPI_PERF_ES_WAVE,
          &SPI_SPI_PERF_GS_BUSY,
          &SPI_SPI_PERF_GS_WAVE,
          &SPI_SPI_PERF_HS_BUSY,
          &SPI_SPI_PERF_HS_WAVE,
          &SPI_SPI_PERF_LS_BUSY,
          &SPI_SPI_PERF_LS_WAVE,
          &SPI_SPI_PERF_PS_CTL_BUSY,
          &SPI_SPI_PERF_VS_BUSY,
          &SPI_SPI_PERF_VS_WAVE,
          }
  },
  {"VGT",
    {
      &VGT_VGT_PERF_VGT_TE11_BUSY,
          }
  },
  {"PA_SU",
    {
      &PA_SU_PERF_PAPC_PA_INPUT_PRIM,
          }
  },
      };

std::vector<std::vector<RegisterConfig*>> registers_by_group_and_counter;

class Metric {
 public:
  virtual const char *name() const = 0;
  virtual void select(GLuint monitor, bool enable) = 0;
  virtual ~Metric() {}
  virtual float value(float gpu_clocks) const = 0;
  explicit Metric(uint group) : m_group_id(group) {}
  uint group() const { return m_group_id; }
 private:
  uint m_group_id;
};

class GPUClocks : public Metric {
 public:
  explicit GPUClocks(uint group) : Metric(group) {}
  const char* name() const { return "GPUClocks"; }
  void select(GLuint monitor, bool enable) {
    // select at least one metric, so we can wait on it
    GRBM_GRBM_PERF_SEL_GUI_ACTIVE.select(monitor, enable);
    return;
  }
  float value(float gpu_clocks) const {
    return gpu_clocks;
  }
};

class VertexShaderClocks : public Metric {
 public:
  explicit VertexShaderClocks(uint group) : Metric(group) {}
  const char* name() const { return "VertexShaderClocks"; }
  void select(GLuint monitor, bool enable) {
    SPI_SPI_PERF_VS_BUSY.select(monitor, enable);
    SPI_SPI_PERF_ES_BUSY.select(monitor, enable);
    // cannot task more than 6 registers in spi
    // SPI_SPI_PERF_LS_BUSY.select(monitor, enable);
    SPI_SPI_PERF_PS_CTL_BUSY.select(monitor, enable);
    SPI_SPI_PERF_VS_WAVE.select(monitor, enable);
    SPI_SPI_PERF_ES_WAVE.select(monitor, enable);
    SPI_SPI_PERF_LS_WAVE.select(monitor, enable);
    GRBM_GRBM_PERF_SEL_GUI_ACTIVE.select(monitor, enable);
    return;
  }
  float value(float gpu_clocks) const {
    float vs_clocks = 0;
    if (SPI_SPI_PERF_VS_WAVE.value)
      vs_clocks = SPI_SPI_PERF_VS_BUSY.value;
    if (SPI_SPI_PERF_ES_WAVE.value)
      vs_clocks = SPI_SPI_PERF_ES_BUSY.value;
    if (SPI_SPI_PERF_LS_WAVE.value)
      // vs_clocks = SPI_SPI_PERF_LS_BUSY.value;
      assert(false);
    if (vs_clocks == 0)
      return 0;
    vs_clocks = vs_clocks / SPI_SPI_PERF_PS_CTL_BUSY.value;
    vs_clocks = vs_clocks * gpu_clocks;
    return vs_clocks;
  }
};

class GPUBusy : public Metric {
 public:
  explicit GPUBusy(uint group) : Metric(group) {}
  const char* name() const { return "GPUBusy"; }
  void select(GLuint monitor, bool enable) {
    GRBM_GRBM_PERF_SEL_GUI_ACTIVE.select(monitor, enable);
    GRBM_GRBM_PERF_SEL_COUNT.select(monitor, enable);
    return;
  }
  float value(float gpu_clocks) const {
    return GRBM_GRBM_PERF_SEL_GUI_ACTIVE.value / GRBM_GRBM_PERF_SEL_COUNT.value;
  }
};


class PrimitivesIn : public Metric {
 public:
  explicit PrimitivesIn(uint group) : Metric(group) {}
  const char* name() const { return "PrimitivesIn"; }
  void select(GLuint monitor, bool enable) {
    PA_SU_PERF_PAPC_PA_INPUT_PRIM.select(monitor, enable);
    return;
  }
  float value(float gpu_clocks) const {
    return PA_SU_PERF_PAPC_PA_INPUT_PRIM.value;
  }
};

class TessellatorBusy : public Metric {
 public:
  explicit TessellatorBusy(uint group) : Metric(group) {}
  const char *name() const { return "TessellatorBusy"; }
  void select(GLuint monitor, bool enable) {
    VGT_VGT_PERF_VGT_TE11_BUSY.select(monitor, enable);
    GRBM_GRBM_PERF_SEL_GUI_ACTIVE.select(monitor, enable);
    return;
  }
  float value(float gpu_clocks) const {
    return 100.0 * VGT_VGT_PERF_VGT_TE11_BUSY.value /
        GRBM_GRBM_PERF_SEL_GUI_ACTIVE.value;
  }
};

class HSBusy : public Metric {
 public:
  explicit HSBusy(uint group) : Metric(group) {}
  const char *name() const { return "HSBusy"; }
  void select(GLuint monitor, bool enable) {
    SPI_SPI_PERF_HS_BUSY.select(monitor, enable);
    SPI_SPI_PERF_HS_WAVE.select(monitor, enable);
    GRBM_GRBM_PERF_SEL_GUI_ACTIVE.select(monitor, enable);
  }
  float value(float gpu_clocks) const {
    float hs_clocks = 0;
    // if (SPI_SPI_PERF_HS_WAVE.value != 0)
      hs_clocks = SPI_SPI_PERF_HS_BUSY.value;
    return 100.0 * hs_clocks / GRBM_GRBM_PERF_SEL_GUI_ACTIVE.value;
  }
};

std::vector<Metric*> public_metrics_by_group {
  new GPUClocks(0),
      new VertexShaderClocks(1),
      new PrimitivesIn(2),
      new TessellatorBusy(3),
      new HSBusy(4),
      // new GPUBusy(2),
      };

std::vector<Metric *> selected_metrics_by_monitor;
struct CounterQuery {
  GLuint begin_query;
  GLuint end_query;
};

std::vector<CounterQuery> queries_by_monitor;

void
AMDPerformanceMonitor::Init() {
  // TODO(majanes): query graphics hw generation.  For now, assume gen8

  // query all groups and counters if necessary
  GLint numGroups;
  GlFunctions::GetPerfMonitorGroupsAMD(&numGroups, 0, NULL);
  std::vector<GLuint> groups(numGroups + 1);
  registers_by_group_and_counter.resize(numGroups);
  GlFunctions::GetPerfMonitorGroupsAMD(&numGroups,
                                       groups.size(), groups.data());
  for (auto group : groups) {
    int maxLen;
    GlFunctions::GetPerfMonitorGroupStringAMD(group, 0, &maxLen, NULL);
    std::vector<char> name(maxLen + 1);
    GlFunctions::GetPerfMonitorGroupStringAMD(group, name.size(),
                                              &maxLen, name.data());
    // add all registers to group/counter lookup
    assert(registers_by_group_and_counter.size() > group);
    auto &registers_to_add = registers_by_group_name[name.data()];
    auto &counter_lookup = registers_by_group_and_counter[group];
    counter_lookup.resize(registers_to_add.size());
    for (auto counter : registers_to_add) {
      if (counter_lookup.size() <= counter->counter)
        counter_lookup.resize(counter->counter + 1);
      counter_lookup[counter->counter] = counter;
      counter->group = group;
      GLuint counter_type;
      GlFunctions::GetPerfMonitorCounterInfoAMD(group, counter->counter,
                                                GL_COUNTER_TYPE_AMD,
                                                &counter_type);
      counter->type = counter_type;
    }
  }
}

void
AMDPerformanceMonitor::GetPerfMonitorGroupsAMD(
    GLint *numGroups, GLsizei groupsSize, GLuint *groups) {
  // one group per supported metric
  const int metrics_count = public_metrics_by_group.size();
  *numGroups = metrics_count;

  for (int i = 0; i < groupsSize && i < metrics_count; ++i) {
    groups[i] = i;
  }
}

void
AMDPerformanceMonitor::GetPerfMonitorCountersAMD(
      GLuint group, GLint *numCounters, GLint *maxActiveCounters,
      GLsizei counterSize, GLuint *counters) {
  // one "counter" (metric) per group
  *numCounters = 1;
  *maxActiveCounters = 1;
  if (counterSize)
    *counters = 1;
}

void
AMDPerformanceMonitor::GetPerfMonitorGroupStringAMD(
    GLuint group, GLsizei bufSize, GLsizei *length, GLchar *groupString) {
  // return metric name
  const char *name = public_metrics_by_group[group]->name();
  *length = strlen(name);
  strncpy(groupString, name, bufSize);
  if (bufSize)
    groupString[bufSize - 1] = '\0';
}

void
AMDPerformanceMonitor::GetPerfMonitorCounterStringAMD(
      GLuint group, GLuint counter, GLsizei bufSize, GLsizei *length,
      GLchar *counterString) {
  // metric name
  assert(counter == 1);
  const char *name = public_metrics_by_group[group]->name();
  *length = strlen(name);
  strncpy(counterString, name, bufSize);
  if (bufSize)
    counterString[bufSize - 1] = '\0';
}

void
AMDPerformanceMonitor::GetPerfMonitorCounterInfoAMD(
    GLuint group, GLuint counter, GLenum pname, void *data) {
  if (pname == GL_COUNTER_TYPE_AMD) {
    GLuint *t = reinterpret_cast<GLuint*>(data);
    *t = GL_FLOAT;
    return;
  }
  assert(pname == GL_COUNTER_RANGE_AMD);
  GLfloat *minmax = reinterpret_cast<GLfloat*>(data);
  *minmax = FLT_MIN;
  ++minmax;
  *minmax = FLT_MAX;
}

void
AMDPerformanceMonitor::GenPerfMonitorsAMD(GLsizei n, GLuint *monitors) {
  GlFunctions::GenPerfMonitorsAMD(n, monitors);
  std::vector<GLuint> queries(2*n);
  GL::GetError();
  GlFunctions::GenQueries(2*n, queries.data());
  assert(!GL::GetError());
  for (int i = 0; i < n; ++i) {
    GLuint monitor = monitors[i];
    if (queries_by_monitor.size() <= monitor)
      queries_by_monitor.resize(monitor + 1);
    queries_by_monitor[monitor].begin_query = queries[2*i];
    queries_by_monitor[monitor].end_query = queries[(2*i)+1];
  }
}

void
AMDPerformanceMonitor::DeletePerfMonitorsAMD(GLsizei n, GLuint *monitors) {
  GlFunctions::DeletePerfMonitorsAMD(n, monitors);
  for (int i = 0; i < n; ++i) {
    GlFunctions::DeleteQueries(
        1, &(queries_by_monitor[monitors[i]].begin_query));
    assert(!GL::GetError());
    GlFunctions::DeleteQueries(
        1, &(queries_by_monitor[monitors[i]].end_query));
    assert(!GL::GetError());
    queries_by_monitor[monitors[i]].begin_query = -1;
    queries_by_monitor[monitors[i]].end_query = -1;
  }
}

void
AMDPerformanceMonitor::SelectPerfMonitorCountersAMD(
      GLuint monitor, GLboolean enable, GLuint group,
      GLint numCounters, GLuint *counterList) {
  // translate counter list to the registers needed for the metric
  if (selected_metrics_by_monitor.size() <= monitor) {
    selected_metrics_by_monitor.resize(monitor + 1);
  }
  if (enable)
    selected_metrics_by_monitor[monitor] = public_metrics_by_group[group];
  else
    selected_metrics_by_monitor[monitor] = NULL;

  assert(numCounters == 1);
  assert(*counterList == 1);
  public_metrics_by_group[group]->select(monitor, enable);
}

void
AMDPerformanceMonitor::BeginPerfMonitorAMD(GLuint monitor) {
  assert(!GL::GetError());
  GlFunctions::BeginPerfMonitorAMD(monitor);
  assert(!GL::GetError());
  GlFunctions::QueryCounter(
      queries_by_monitor[monitor].begin_query, GL_TIMESTAMP);
  assert(!GL::GetError());
}

void
AMDPerformanceMonitor::EndPerfMonitorAMD(GLuint monitor) {
  assert(!GL::GetError());
  GlFunctions::EndPerfMonitorAMD(monitor);
  GlFunctions::QueryCounter(
      queries_by_monitor[monitor].end_query, GL_TIMESTAMP);
}

void
AMDPerformanceMonitor::GetPerfMonitorCounterDataAMD(
      GLuint monitor, GLenum pname, GLsizei dataSize,
      GLuint *data, GLint *bytesWritten) {
  // parse the data, translate into the metric
  switch (pname) {
    case GL_PERFMON_RESULT_AVAILABLE_AMD:
      GlFunctions::GetPerfMonitorCounterDataAMD(
          monitor, GL_PERFMON_RESULT_AVAILABLE_AMD,
          dataSize, data, bytesWritten);
      assert(!GL::GetError());
      if (*data) {
        // begin query must also complete
        GlFunctions::GetQueryObjectiv(
            queries_by_monitor[monitor].begin_query,
            GL_QUERY_RESULT_AVAILABLE,
            reinterpret_cast<GLint*>(data));
        assert(!GL::GetError());
      }
      if (*data) {
        // end query must also complete
        GlFunctions::GetQueryObjectiv(
            queries_by_monitor[monitor].end_query,
            GL_QUERY_RESULT_AVAILABLE,
            reinterpret_cast<GLint*>(data));
        assert(!GL::GetError());
      }
      return;
    case GL_PERFMON_RESULT_SIZE_AMD:
      if (*bytesWritten) {
        assert(*bytesWritten == sizeof(GLuint));
        // this implementation always returns a single float metric.
        *data = 2*sizeof(GLuint) + sizeof(GLfloat);
      }
      return;
    case GL_PERFMON_RESULT_AMD: {
      GLuint data_size;
      GLint data_bytes_written;

      GLuint64 time_start, time_end;
      GlFunctions::GetQueryObjectui64v(
          queries_by_monitor[monitor].begin_query,
          GL_QUERY_RESULT, &time_start);
      GlFunctions::GetQueryObjectui64v(
          queries_by_monitor[monitor].end_query,
          GL_QUERY_RESULT, &time_end);
      const float gpu_clocks = (time_end - time_start);

      GlFunctions::GetPerfMonitorCounterDataAMD(
          monitor, GL_PERFMON_RESULT_SIZE_AMD,
          sizeof(GLint), &data_size, &data_bytes_written);
      assert(data_bytes_written == sizeof(GLint));

      std::vector<unsigned char> buf(data_size);
      GlFunctions::GetPerfMonitorCounterDataAMD(
          monitor, GL_PERFMON_RESULT_AMD,
          sizeof(data_size),
          reinterpret_cast<GLuint*>(buf.data()),
          &data_bytes_written);
      const unsigned char *buf_ptr = buf.data();
      const unsigned char *buf_end = buf_ptr + data_bytes_written;
      while (buf_ptr < buf_end) {
        const GLuint *group = reinterpret_cast<const GLuint *>(buf_ptr);
        const GLuint *counter = group + 1;
        buf_ptr += 2*sizeof(GLuint);

        RegisterConfig *r
            = registers_by_group_and_counter[*group][*counter];

        buf_ptr = r->parse(buf_ptr);
      }
      *bytesWritten = 2 * sizeof(GLuint) + sizeof(float);
      const Metric *metric = selected_metrics_by_monitor[monitor];
      *data = metric->group();
      data += 1;
      *data = 1;  // counter
      data += 1;
      *reinterpret_cast<float*>(data) = metric->value(gpu_clocks);
      break;
    }
    default:
      assert(false);
  }
}
