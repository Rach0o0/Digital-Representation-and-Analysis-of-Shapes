# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/rachid/.cache/CPM/polyscope/9a2fab0cfe13126067bbcef89aa29c1042ae9e90"
  "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/polyscope-build"
  "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/polyscope-subbuild/polyscope-populate-prefix"
  "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/polyscope-subbuild/polyscope-populate-prefix/tmp"
  "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/polyscope-subbuild/polyscope-populate-prefix/src/polyscope-populate-stamp"
  "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/polyscope-subbuild/polyscope-populate-prefix/src"
  "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/polyscope-subbuild/polyscope-populate-prefix/src/polyscope-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/polyscope-subbuild/polyscope-populate-prefix/src/polyscope-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/rachid/digital_representation/code-skeleton-csc_51074_ep_2026/TDS/TD1/TD1/build/_deps/polyscope-subbuild/polyscope-populate-prefix/src/polyscope-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
