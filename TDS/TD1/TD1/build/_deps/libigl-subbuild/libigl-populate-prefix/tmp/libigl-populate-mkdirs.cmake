# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/rachid/.cache/CPM/libigl/74976ac685465834ad94885903c2e3cede814757"
  "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/libigl-build"
  "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/libigl-subbuild/libigl-populate-prefix"
  "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/libigl-subbuild/libigl-populate-prefix/tmp"
  "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/libigl-subbuild/libigl-populate-prefix/src/libigl-populate-stamp"
  "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/libigl-subbuild/libigl-populate-prefix/src"
  "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/libigl-subbuild/libigl-populate-prefix/src/libigl-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/libigl-subbuild/libigl-populate-prefix/src/libigl-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/libigl-subbuild/libigl-populate-prefix/src/libigl-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
