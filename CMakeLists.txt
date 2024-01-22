cmake_minimum_required (VERSION 3.16)

## CUSTOMISE

# Define the application name and version.
project (app-template VERSION 1.0.0)

## BUILD

# Make Release default build type
if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE
         Release
         CACHE STRING "Choose the type of build, options are: Debug Release Coverage RelWithDebInfo MinSizeRel." FORCE
    )
endif ()

# Specify the directories where to store the built archives, libraries and executables
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Messages
string (ASCII 27 Esc)
set (FontBold "${Esc}[1m")
set (FontReset "${Esc}[m")

list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Use ccache.
include (ccache)
require_ccache ()

set (CPM_INDENT "  CMake Package Manager CPM: ")
include (CPM)
include (CPMGetSystemPackage)
CPMUsePackageLock (${CMAKE_CURRENT_LIST_DIR}/cmake/package-lock.cmake)

# CPMGetSystemPackage (hibf)
CPMGetSystemPackage (sharg)
CPMGetSystemPackage (seqan3)

# Allow to include CMake scripts from seqan3.
list (APPEND CMAKE_MODULE_PATH "${seqan3_SOURCE_DIR}/test/cmake/")
# Allow to include CMake scripts from the app-template.
list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/test/cmake/")

# Add the application.
add_subdirectory (src)
message (STATUS "${FontBold}You can run `make` to build the application.${FontReset}")

## DOCUMENTATION

add_subdirectory (doc EXCLUDE_FROM_ALL)

## TEST

enable_testing ()
add_subdirectory (test EXCLUDE_FROM_ALL)
