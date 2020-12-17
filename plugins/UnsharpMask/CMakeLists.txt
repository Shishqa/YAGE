add_library(UnsharpMask SHARED)

set(INCROOT ${YAGE_SOURCE_DIR}/plugins/UnsharpMask)

target_include_directories(UnsharpMask
  PRIVATE
    ${INCROOT}
  )

target_sources(UnsharpMask
  PUBLIC
    ${INCROOT}/UnsharpMask.hpp
  PRIVATE
  UnsharpMask.cpp
  )

target_link_libraries(UnsharpMask
  PUBLIC
    PluginAPI
  )

target_compile_features(UnsharpMask
  PUBLIC
    cxx_std_17
  )