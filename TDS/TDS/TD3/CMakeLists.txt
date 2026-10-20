cmake_minimum_required(VERSION 3.20)

project("Bezier Curves")

# Maybe stop from CMAKEing in the wrong place
if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Source and build directories cannot be the same. Go use the /build directory.")
endif()

### Configure output locations
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

### Compiler options
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 ) # Emit a compile flags file to support completion engines 

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD 17)

list(PREPEND CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}/../cmake/settings
    ${PROJECT_SOURCE_DIR}/../cmake/recipes
)
include(set_cpm_cache)
# === Load CPM.cmake ===
include(CPM)

# === Fetch dependencies ===
include(libigl)
include(polyscope)


add_executable(
    td_3_executable
  src/main.cpp
)

add_library(td_3_lib
  src/Bezier.cpp 
)

target_link_libraries(td_3_lib
polyscope
igl::core
)

target_include_directories(
td_3_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)


# Link settings
target_link_libraries(td_3_executable polyscope igl::core td_3_lib )

target_compile_definitions(td_3_executable PRIVATE PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")


#### Do the unit testing
include(googletest)


add_executable(unit_tests tests/unittests.cpp)
target_link_libraries(unit_tests td_3_lib gtest gtest_main)

target_include_directories(unit_tests 
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(unit_tests PRIVATE PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

add_test(
  NAME AllTests 
  COMMAND unit_tests 
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)