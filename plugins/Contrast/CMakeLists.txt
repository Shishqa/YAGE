add_library(Contrast SHARED)

set(INCROOT ${YAGE_SOURCE_DIR}/plugins/Contrast)

target_include_directories(Contrast
  PRIVATE
    ${INCROOT}
  )

target_sources(Contrast
  PUBLIC
    ${INCROOT}/Contrast.hpp
  PRIVATE
    Contrast.cpp
  )

target_link_libraries(Contrast
  PUBLIC
    PluginAPI
  )

target_compile_features(Contrast
  PUBLIC
    cxx_std_17
  )