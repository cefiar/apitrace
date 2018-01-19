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

#ifndef GLFRAME_AMD_PERFORMANCE_MONITOR_HPP__
#define GLFRAME_AMD_PERFORMANCE_MONITOR_HPP__

#include <GL/gl.h>
#include <GL/glext.h>

namespace glretrace {

class AMDPerformanceMonitor {
 public:
  static void Init();
  static void GetPerfMonitorGroupsAMD(
      GLint *numGroups, GLsizei groupsSize, GLuint *groups);
  static void GetPerfMonitorCountersAMD(
      GLuint group, GLint *numCounters, GLint *maxActiveCounters,
      GLsizei counterSize, GLuint *counters);
  static void GetPerfMonitorGroupStringAMD(
      GLuint group, GLsizei bufSize, GLsizei *length, GLchar *groupString);
  static void GetPerfMonitorCounterStringAMD(
      GLuint group, GLuint counter, GLsizei bufSize, GLsizei *length,
      GLchar *counterString);
  static void GetPerfMonitorCounterInfoAMD(
      GLuint group, GLuint counter, GLenum pname, void *data);
  static void GenPerfMonitorsAMD(GLsizei n, GLuint *monitors);
  static void DeletePerfMonitorsAMD(GLsizei n, GLuint *monitors);
  static void SelectPerfMonitorCountersAMD(
      GLuint monitor, GLboolean enable, GLuint group,
      GLint numCounters, GLuint *counterList);
  static void BeginPerfMonitorAMD(GLuint monitor);
  static void EndPerfMonitorAMD(GLuint monitor);
  static void GetPerfMonitorCounterDataAMD(
      GLuint monitor, GLenum pname, GLsizei dataSize,
      GLuint *data, GLint *bytesWritten);

 private:
  AMDPerformanceMonitor();
};

}  // namespace glretrace

#endif  // GLFRAME_AMD_PERFORMANCE_MONITOR_HPP__
