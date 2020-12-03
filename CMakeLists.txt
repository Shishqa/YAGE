cmake_minimum_required(VERSION 3.8)

project(YAGE
  VERSION 0.1
  LANGUAGES CXX
  )

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  set(DEFAULT_BUILD_TYPE "Release")

  set(CMAKE_CXX_EXTENSIONS OFF)

  set(RELEASE_FLAGS " \
    -O3 \
    -Wno-unused-parameter \
    -msse4.2 \
    -march=native \
  ")

  set(DEBUG_FLAGS " \
    -g \
    -O3 \
    -msse4.2 \
    -march=native \
    -Wconversion \
    -Wlogical-op \
    -Wshift-overflow=2 \
		-Wduplicated-cond \
		-Wno-unused-parameter \
		-Wcast-qual -Wcast-align \
		-D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC \
		-D_FORTIFY_SOURCE=2 -fsanitize=address \
		-fsanitize=undefined -fno-sanitize-recover \
		-fstack-protector -Wno-format-nonliteral \
    -fno-omit-frame-pointer \
  ")

  set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${DEBUG_FLAGS}")
  set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} ${DEBUG_FLAGS}")

  set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${RELEASE_FLAGS}")
  set (CMAKE_LINKER_FLAGS_RELEASE "${CMAKE_LINKER_FLAGS_RELEASE} ${RELEASE_FLAGS}")

  if (MSVC)
    add_compile_options(/W3 /WX)
  else()
    add_compile_options(-W -Wall -Wextra -Wpedantic -Werror -pedantic-errors)
  endif()

  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()





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
    src/main.cpp
    src/YAGE.cpp
  )

target_link_libraries(yage
  PUBLIC
    ShishGL
    YAGE-ToolManager
    YAGE-Tools
    YAGE-ImageManager
    YAGE-Panels
  )

add_subdirectory(src)
add_subdirectory(src/ColorUtils)
add_subdirectory(src/ImageManager)
add_subdirectory(src/Panels)
add_subdirectory(src/ToolManager)
add_subdirectory(../00_ShishGL ShishGL)