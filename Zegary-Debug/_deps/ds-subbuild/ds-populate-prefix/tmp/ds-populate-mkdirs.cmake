# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "A:/studia/IPZ/MainDashboard/Zegary-Debug/_deps/ds-src"
  "A:/studia/IPZ/MainDashboard/Zegary-Debug/_deps/ds-build"
  "A:/studia/IPZ/MainDashboard/Zegary-Debug/_deps/ds-subbuild/ds-populate-prefix"
  "A:/studia/IPZ/MainDashboard/Zegary-Debug/_deps/ds-subbuild/ds-populate-prefix/tmp"
  "A:/studia/IPZ/MainDashboard/Zegary-Debug/_deps/ds-subbuild/ds-populate-prefix/src/ds-populate-stamp"
  "A:/studia/IPZ/MainDashboard/Zegary-Debug/_deps/ds-subbuild/ds-populate-prefix/src"
  "A:/studia/IPZ/MainDashboard/Zegary-Debug/_deps/ds-subbuild/ds-populate-prefix/src/ds-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "A:/studia/IPZ/MainDashboard/Zegary-Debug/_deps/ds-subbuild/ds-populate-prefix/src/ds-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "A:/studia/IPZ/MainDashboard/Zegary-Debug/_deps/ds-subbuild/ds-populate-prefix/src/ds-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
