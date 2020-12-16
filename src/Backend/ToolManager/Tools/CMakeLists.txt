add_library(YAGE-Tools)

set(INCROOT ${YAGE_SOURCE_DIR}/include/YAGE/Backend/ToolManager/Tools)

target_include_directories(YAGE-Tools
  PUBLIC
    ${INCROOT}
  )

target_sources(YAGE-Tools
  PUBLIC
    ${INCROOT}/Tools.hpp
  PRIVATE
    ${INCROOT}/Tool.hpp
    ${INCROOT}/Pencil.hpp
    ${INCROOT}/Eraser.hpp
    ${INCROOT}/Rectangle.hpp
    ${INCROOT}/Dropper.hpp
  Pencil.cpp
  )

target_link_libraries(YAGE-Tools
  PUBLIC
    YAGE-ToolManager
  )