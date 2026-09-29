cmake_minimum_required(VERSION 3.20)

project("Interpolation of Curves")

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
    td_2_executable
    src/main.cpp
)

# Link settings

add_library(td_2_lib
  src/linear.cpp 
  src/hermite.cpp 
  src/lagrange.cpp 
  src/cubic.cpp
)

target_compile_definitions(td_2_executable PRIVATE PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")
target_include_directories(td_2_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(td_2_lib 
  igl::core
  polyscope
)

target_link_libraries(td_2_executable polyscope igl::core td_2_lib)

#### Do the unit testing
include(googletest)


