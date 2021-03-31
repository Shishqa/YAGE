add_library(YAGE-Backend)

set(INCROOT ${YAGE_SOURCE_DIR}/include/YAGE/Backend/)

target_include_directories(YAGE-Backend
  PUBLIC
    ${INCROOT}
  )

target_sources(YAGE-Backend
  PUBLIC
    ${INCROOT}/SessionManager.hpp
    ${INCROOT}/PluginManager.hpp
    ${INCROOT}/json.hpp
  PRIVATE
    PluginManager.cpp
    PluginTool.cpp
    SessionManager.cpp
  )

target_link_libraries(YAGE-Backend
  PUBLIC
    ShishGL
    PluginAPI
    YAGE-ImageManager
    YAGE-ToolManager
    YAGE-Tools
    dl
  )

add_subdirectory(ImageManager)
add_subdirectory(ToolManager)
