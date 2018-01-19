set (AMD_IMPL_SOURCES
  glframe_amd_performance_monitor.cpp
  glframe_amd_performance_monitor.hpp
  )


add_library(amd_perf_monitor_impl
  gfx_8_0_enum.h
  ${AMD_IMPL_SOURCES}
  )

Lint( AMD_IMPL_SOURCES )
