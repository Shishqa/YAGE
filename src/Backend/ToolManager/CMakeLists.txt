add_library(YAGE-ToolManager)

set(INCROOT ${YAGE_SOURCE_DIR}/include/YAGE/Backend/ToolManager)

target_include_directories(YAGE-ToolManager
  PUBLIC
  ${INCROOT}
  )

target_sources(YAGE-ToolManager
  PUBLIC
    ${INCROOT}/ToolManager.hpp
  PRIVATE
    ToolManager.cpp
  )

target_link_libraries(YAGE-ToolManager
  PUBLIC
    ShishGL
    YAGE-Properties
    YAGE-Tools
  )

add_subdirectory(Tools)
add_subdirectory(Properties)
