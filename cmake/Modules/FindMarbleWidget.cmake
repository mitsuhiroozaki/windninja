# Find MarbleWidget
# ~~~~~~~~~
# Copyright (c) 2007, Martin Dobias <wonder.sk at gmail.com>
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#
# CMake module to search for Proj library
#
# If it's found it sets PROJ_FOUND to TRUE
# and following variables are set:
#    PROJ_INCLUDE_DIR
#    PROJ_LIBRARY

# FIND_PATH and FIND_LIBRARY normally search standard locations
# before the specified paths. To search non-standard paths first,
# FIND_* is invoked first with specified paths and NO_DEFAULT_PATH
# and then again with no specified paths to search the default
# locations. When an earlier FIND_* succeeds, subsequent FIND_*s
# searching for the same item do nothing. 

# try to use framework on mac
# want clean framework path, not unix compatibility path
#
#FROM COPYING-CMAKE-SCRIPTS
#THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
#IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
#OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
#IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
#INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
#NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
#THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

IF (APPLE)
  IF (CMAKE_FIND_FRAMEWORK MATCHES "FIRST"
      OR CMAKE_FRAMEWORK_PATH MATCHES "ONLY"
      OR NOT CMAKE_FIND_FRAMEWORK)
    SET (CMAKE_FIND_FRAMEWORK_save ${CMAKE_FIND_FRAMEWORK} CACHE STRING "" FORCE)
    SET (CMAKE_FIND_FRAMEWORK "ONLY" CACHE STRING "" FORCE)
    #FIND_PATH(PROJ_INCLUDE_DIR PROJ/proj_api.h)
    FIND_LIBRARY(PROJ_LIBRARY PROJ)
    IF (PROJ_LIBRARY)
      # FIND_PATH doesn't add "Headers" for a framework
      SET (PROJ_INCLUDE_DIR ${PROJ_LIBRARY}/Headers CACHE PATH "Path to a file.")
    ENDIF (PROJ_LIBRARY)
    SET (CMAKE_FIND_FRAMEWORK ${CMAKE_FIND_FRAMEWORK_save} CACHE STRING "" FORCE)
  ENDIF ()
ENDIF (APPLE)

FIND_PATH(PROJ_INCLUDE_DIR proj_api.h
  "$ENV{LIB_DIR}/include/proj"
  "$ENV{LIB_DIR}/include"
  #mingw
  c:/msys/local/include
  NO_DEFAULT_PATH
  )
FIND_PATH(PROJ_INCLUDE_DIR proj_api.h)

FIND_LIBRARY(PROJ_LIBRARY NAMES proj PATHS
  "$ENV{LIB_DIR}/lib"
  #mingw
  c:/msys/local/lib
  NO_DEFAULT_PATH
  )
FIND_LIBRARY(PROJ_LIBRARY NAMES proj)

IF (PROJ_INCLUDE_DIR AND PROJ_LIBRARY)
   SET(PROJ_FOUND TRUE)
ENDIF (PROJ_INCLUDE_DIR AND PROJ_LIBRARY)


IF (PROJ_FOUND)

   IF (NOT PROJ_FIND_QUIETLY)
      MESSAGE(STATUS "Found Proj: ${PROJ_LIBRARY}")
   ENDIF (NOT PROJ_FIND_QUIETLY)

ELSE (PROJ_FOUND)

   IF (PROJ_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find Proj")
   ENDIF (PROJ_FIND_REQUIRED)

ENDIF (PROJ_FOUND)
