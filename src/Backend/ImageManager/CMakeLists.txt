add_library(YAGE-ImageManager)

set(INCROOT ${YAGE_SOURCE_DIR}/include/YAGE/Backend/ImageManager)

target_include_directories(YAGE-ImageManager
  PUBLIC
    ${INCROOT}
  )

target_sources(YAGE-ImageManager
  PUBLIC
    ${INCROOT}/ImageManager.hpp
  PRIVATE
    ImageManager.cpp
  )

target_link_libraries(YAGE-ImageManager
  PUBLIC
    ShishGL
  )