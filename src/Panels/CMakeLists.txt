add_library(YAGE-Panels)

set(INCROOT ${YAGE_SOURCE_DIR}/include/YAGE/Panels)

target_include_directories(YAGE-Panels
  PUBLIC
    ${INCROOT}
  )

target_sources(YAGE-Panels
  PUBLIC
    ${INCROOT}/ColorPicker.hpp
  PRIVATE
    ColorPicker.cpp
  )

target_link_libraries(YAGE-Panels
  PUBLIC
    ShishGL
    YAGE-ColorUtils
    YAGE-ImageManager
  )