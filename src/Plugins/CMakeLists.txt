add_library(YAGE-Plugins)

set(INCROOT ${YAGE_SOURCE_DIR}/include/YAGE/Plugins)

target_include_directories(YAGE-Plugins
  PUBLIC
    ${INCROOT}
  )

target_sources(YAGE-Plugins
  PUBLIC
    ${INCROOT}/PluginManager.hpp
    ${INCROOT}/json.hpp
  PRIVATE
    PluginManager.cpp
  )

target_link_libraries(YAGE-Plugins
  PUBLIC
    ShishGL
    PluginAPI
    YAGE-ToolManager
  )