add_library(YAGE-Properties)

set(INCROOT ${YAGE_SOURCE_DIR}/include/YAGE/Backend/ToolManager/Properties)

target_include_directories(YAGE-Properties
  PUBLIC
    ${INCROOT}
  )

target_sources(YAGE-Properties
  PUBLIC
    ${INCROOT}/IProperty.hpp
    ${INCROOT}/DefaultProperties.hpp
    ${INCROOT}/ColorPicker.hpp
    ${INCROOT}/NumberPickers.hpp
    ${INCROOT}/Stroke.hpp
  PRIVATE
    Property.cpp
    Stroke.cpp
    ColorPicker.cpp
    DefaultProperties.cpp
  )

target_link_libraries(YAGE-Properties
  PUBLIC
    ShishGL
    YAGE-ColorUtils
  )