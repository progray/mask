# FindHiredis
# --------
#
# Find hiredis
#
# Find the hiredis includes and library.  Once done this will define
#
#   HIREDIS_INCLUDE_DIRS   	 - where to find hiredis.h, etc.
#   HIREDIS_LIBRARIES      	 - List of libraries when using hiredis.
#   HIREDIS_STATIC_LIBRARIES      - List of static libraries when using hiredis.
#   HIREDIS_FOUND          	 - True if hiredis found.
#

#=============================================================================
# Copyright 2001-2011 Kitware, Inc.
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

find_path(HIREDIS_INCLUDE_DIR NAMES hiredis/hiredis.h)
find_library(HIREDIS_LIBRARY  NAMES hiredis)
find_library(HIREDIS_STATIC_LIBRARY  NAMES libhiredis.a)

mark_as_advanced(HIREDIS_LIBRARY HIREDIS_STATIC_LIBRARY HIREDIS_INCLUDE_DIR)

# handle the QUIETLY and REQUIRED arguments and set HIREDIS_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Hiredis REQUIRED_VARS HIREDIS_LIBRARY HIREDIS_STATIC_LIBRARY HIREDIS_INCLUDE_DIR
                                          VERSION_VAR HIREDIS_VERSION_STRING)

if(HIREDIS_FOUND)
    set(HIREDIS_INCLUDE_DIRS ${HIREDIS_INCLUDE_DIR})
    set(HIREDIS_LIBRARIES ${HIREDIS_LIBRARY})
    set(HIREDIS_STATIC_LIBRARIES ${HIREDIS_STATIC_LIBRARY})
    message(STATUS "HIREDIS_INCLUDE_DIRS ${HIREDIS_INCLUDE_DIRS}")
    message(STATUS "HIREDIS_LIBRARIES ${HIREDIS_LIBRARIES}")
    message(STATUS "HIREDIS_STATIC_LIBRARIES ${HIREDIS_STATIC_LIBRARIES}")
endif()

