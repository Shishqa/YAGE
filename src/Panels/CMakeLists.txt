add_library(YAGE-Panels)

set(INCROOT ${YAGE_SOURCE_DIR}/include/YAGE/Panels)

target_include_directories(YAGE-Panels
  PUBLIC
    ${INCROOT}
  )

target_sources(YAGE-Panels
  PUBLIC
    ${INCROOT}/MainPanels.hpp
    ${INCROOT}/Canvas.hpp
    ${INCROOT}/LayerList.hpp
    ${INCROOT}/ToolList.hpp
    ${INCROOT}/PropertyList.hpp
    ${INCROOT}/ColorPicker.hpp
    ${INCROOT}/ThicknessPicker.hpp
  PRIVATE
    MainPanels.cpp
    Canvas.cpp
    LayerList.cpp
    ToolList.cpp
    PropertyList.cpp
    ColorPicker.cpp
  )

target_link_libraries(YAGE-Panels
  PUBLIC
    ShishGL
    YAGE-ColorUtils
    YAGE-Backend
  )