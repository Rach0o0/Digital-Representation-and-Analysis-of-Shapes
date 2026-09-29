# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/rachid/.cache/CPM/googletest/c160b1bff2c41876020e2faec6695adcc9059860"
  "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/googletest-build"
  "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/googletest-subbuild/googletest-populate-prefix"
  "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
