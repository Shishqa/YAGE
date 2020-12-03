add_library(YAGE-Panels)

set(INCROOT ${YAGE_SOURCE_DIR}/include/YAGE/Panels)

target_include_directories(YAGE-Panels
  PUBLIC
    ${INCROOT}
  )

target_sources(YAGE-Panels
  PUBLIC
    ${INCROOT}/MainPanels.hpp
    ${INCROOT}/ToolList.hpp
    ${INCROOT}/ColorPicker.hpp
    ${INCROOT}/LayerSelector.hpp
  PRIVATE
    ColorPicker.cpp
  )

target_link_libraries(YAGE-Panels
  PUBLIC
    ShishGL
    YAGE-ColorUtils
    YAGE-ImageManager
  )