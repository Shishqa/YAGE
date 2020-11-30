add_library(YAGE-ImageManager)

set(INCROOT ${YAGE_SOURCE_DIR}/include/YAGE/ImageManager)

target_include_directories(YAGE-ImageManager
  PUBLIC
    ${INCROOT}
  )

target_sources(YAGE-ImageManager
  PUBLIC
    ${INCROOT}/ImageManager.hpp
    ${INCROOT}/Canvas.hpp
  PRIVATE
    ImageManager.cpp
    Canvas.cpp
  )

target_link_libraries(YAGE-ImageManager
  PUBLIC
    ShishGL
    YAGE-ToolManager
    YAGE-Tools
  )