add_library(YAGE-ColorUtils)

set(INCROOT ${YAGE_SOURCE_DIR}/include/YAGE/ColorUtils)

target_include_directories(YAGE-ColorUtils
  PUBLIC
    ${INCROOT}
  )

target_sources(YAGE-ColorUtils
  PUBLIC
    ${INCROOT}/Convert.hpp
  PRIVATE
    Convert.cpp
  )

target_link_libraries(YAGE-ColorUtils
  PUBLIC
    ShishGL
  )