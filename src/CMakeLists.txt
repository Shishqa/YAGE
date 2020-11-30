add_executable(yage)

set(INCROOT ${YAGE_SOURCE_DIR}/include/YAGE)

target_include_directories(yage
  PUBLIC
    ${INCROOT}
  )

target_sources(yage
  PUBLIC
    ${INCROOT}/YAGE.hpp
  PRIVATE
    main.cpp
    YAGE.cpp
  )

target_link_libraries(yage
  PUBLIC
    ShishGL
    YAGE-ToolManager
    YAGE-Tools
    YAGE-ImageManager
    YAGE-Panels
  )

add_subdirectory(ToolManager)
add_subdirectory(ImageManager)
add_subdirectory(ColorUtils)
add_subdirectory(Panels)