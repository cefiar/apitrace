include_directories (
  ${CMAKE_SOURCE_DIR}/retrace/daemon
  )

set (AMD_GPA_SOURCES
  glframe_metrics_amd_gpa.cpp
  glframe_metrics_amd_gpa.hpp
  )

add_library(amdgpa
  ${AMD_GPA_SOURCES}
  )
  
Lint(AMD_GPA_SOURCES)

