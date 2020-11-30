add_library(YAGE-Properties)

set(INCROOT ${YAGE_SOURCE_DIR}/include/YAGE/ToolManager/Properties)

target_include_directories(YAGE-Properties
  PUBLIC
    ${INCROOT}
  )

target_sources(YAGE-Properties
  PUBLIC
    ${INCROOT}/Stroke.hpp
  PRIVATE
    Stroke.cpp
  )

target_link_libraries(YAGE-Properties
  PUBLIC
    ShishGL
  )