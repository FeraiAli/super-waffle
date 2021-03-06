# - Locate SDL2_net library
# This module defines:
#  SDL2_NET_LIBRARIES, the name of the library to link against
#  SDL2_NET_INCLUDE_DIRS, where to find the headers
#  SDL2_NET_FOUND, if false, do not try to link against
#  SDL2_NET_VERSION_STRING - human-readable string containing the version of SDL2_net
#
# $SDL2DIR is an environment variable that would
# correspond to the ./configure --prefix=$SDL2DIR
# used in building SDL2.
#
# Created by Eric Wing. This was influenced by the FindSDL.cmake
# module, but with modifications to recognize OS X frameworks and
# additional Unix paths (FreeBSD, etc).

#=============================================================================
# Copyright 2005-2009 Kitware, Inc.
# Copyright 2012 Benjamin Eikel
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

set(SDL2_DIR "" CACHE PATH "Path to the directory where SDL2 is located")
set(SDL2_NET_DIR "" CACHE PATH "Path to the directory where SDL2_Net is located")

find_path(SDL2_NET_INCLUDE_DIR SDL_net.h
  HINTS
    ENV SDL2NETDIR
    ENV SDL2DIR
    ${SDL2_DIR}
    ${SDL2_NET_DIR}
  PATH_SUFFIXES include/SDL2 include
)

find_library(SDL2_NET_LIBRARY
  NAMES SDL2_net
  HINTS
    ENV SDL2NETDIR
    ENV SDL2DIR
    ${SDL2_DIR}
    ${SDL2_NET_DIR}
  PATH_SUFFIXES lib
)

if(SDL2_NET_INCLUDE_DIR AND EXISTS "${SDL2_NET_INCLUDE_DIR}/SDL_net.h")
  file(STRINGS "${SDL2_NET_INCLUDE_DIR}/SDL_net.h" SDL2_NET_VERSION_MAJOR_LINE REGEX "^#define[ \t]+SDL_NET_MAJOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${SDL2_NET_INCLUDE_DIR}/SDL_net.h" SDL2_NET_VERSION_MINOR_LINE REGEX "^#define[ \t]+SDL_NET_MINOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${SDL2_NET_INCLUDE_DIR}/SDL_net.h" SDL2_NET_VERSION_PATCH_LINE REGEX "^#define[ \t]+SDL_NET_PATCHLEVEL[ \t]+[0-9]+$")
  string(REGEX REPLACE "^#define[ \t]+SDL_NET_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_NET_VERSION_MAJOR "${SDL2_NET_VERSION_MAJOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL_NET_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_NET_VERSION_MINOR "${SDL2_NET_VERSION_MINOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL_NET_PATCHLEVEL[ \t]+([0-9]+)$" "\\1" SDL2_NET_VERSION_PATCH "${SDL2_NET_VERSION_PATCH_LINE}")
  set(SDL2_NET_VERSION_STRING ${SDL2_NET_VERSION_MAJOR}.${SDL2_NET_VERSION_MINOR}.${SDL2_NET_VERSION_PATCH})
  unset(SDL2_NET_VERSION_MAJOR_LINE)
  unset(SDL2_NET_VERSION_MINOR_LINE)
  unset(SDL2_NET_VERSION_PATCH_LINE)
  unset(SDL2_NET_VERSION_MAJOR)
  unset(SDL2_NET_VERSION_MINOR)
  unset(SDL2_NET_VERSION_PATCH)
endif()

set(SDL2_NET_LIBRARIES ${SDL2_NET_LIBRARY})
set(SDL2_NET_INCLUDE_DIRS ${SDL2_NET_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

mark_as_advanced(SDL2_NET_LIBRARY SDL2_NET_INCLUDE_DIR)

find_package_handle_standard_args(SDL2_net
                                  REQUIRED_VARS SDL2_NET_LIBRARIES SDL2_NET_INCLUDE_DIRS
                                  VERSION_VAR SDL2_NET_VERSION_STRING
                                  FAIL_MESSAGE "Could NOT find SDL2_Net: Set SDL2_NET_DIR to a directory containing the folders 'include' and 'lib' or set SDL2_NET_LIBRARY and SDL2_NET_INCLUDE_DIR directly")

mark_as_advanced(SDL2_DIR SDL2_NET_DIR)
