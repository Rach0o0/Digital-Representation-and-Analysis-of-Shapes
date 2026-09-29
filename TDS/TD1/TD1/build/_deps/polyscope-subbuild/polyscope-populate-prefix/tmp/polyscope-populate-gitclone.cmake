# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

if(EXISTS "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/polyscope-subbuild/polyscope-populate-prefix/src/polyscope-populate-stamp/polyscope-populate-gitclone-lastrun.txt" AND EXISTS "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/polyscope-subbuild/polyscope-populate-prefix/src/polyscope-populate-stamp/polyscope-populate-gitinfo.txt" AND
  "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/polyscope-subbuild/polyscope-populate-prefix/src/polyscope-populate-stamp/polyscope-populate-gitclone-lastrun.txt" IS_NEWER_THAN "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/polyscope-subbuild/polyscope-populate-prefix/src/polyscope-populate-stamp/polyscope-populate-gitinfo.txt")
  message(STATUS
    "Avoiding repeated git clone, stamp file is up to date: "
    "'/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/polyscope-subbuild/polyscope-populate-prefix/src/polyscope-populate-stamp/polyscope-populate-gitclone-lastrun.txt'"
  )
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/home/rachid/.cache/CPM/polyscope/9a2fab0cfe13126067bbcef89aa29c1042ae9e90"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/home/rachid/.cache/CPM/polyscope/9a2fab0cfe13126067bbcef89aa29c1042ae9e90'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git"
            clone --no-checkout --depth 1 --no-single-branch --config "advice.detachedHead=false" "https://github.com/nmwsharp/polyscope.git" "9a2fab0cfe13126067bbcef89aa29c1042ae9e90"
    WORKING_DIRECTORY "/home/rachid/.cache/CPM/polyscope"
    RESULT_VARIABLE error_code
  )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once: ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/nmwsharp/polyscope.git'")
endif()

execute_process(
  COMMAND "/usr/bin/git"
          checkout "master" --
  WORKING_DIRECTORY "/home/rachid/.cache/CPM/polyscope/9a2fab0cfe13126067bbcef89aa29c1042ae9e90"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'master'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/bin/git" 
            submodule update --recursive --init 
    WORKING_DIRECTORY "/home/rachid/.cache/CPM/polyscope/9a2fab0cfe13126067bbcef89aa29c1042ae9e90"
    RESULT_VARIABLE error_code
  )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/home/rachid/.cache/CPM/polyscope/9a2fab0cfe13126067bbcef89aa29c1042ae9e90'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/polyscope-subbuild/polyscope-populate-prefix/src/polyscope-populate-stamp/polyscope-populate-gitinfo.txt" "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/polyscope-subbuild/polyscope-populate-prefix/src/polyscope-populate-stamp/polyscope-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/polyscope-subbuild/polyscope-populate-prefix/src/polyscope-populate-stamp/polyscope-populate-gitclone-lastrun.txt'")
endif()
