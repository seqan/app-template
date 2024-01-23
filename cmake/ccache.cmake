# --------------------------------------------------------------------------------------------------
# Copyright (c) 2006-2023, Knut Reinert & Freie Universität Berlin
# Copyright (c) 2016-2023, Knut Reinert & MPI für molekulare Genetik
# This file may be used, modified and/or redistributed under the terms of the 3-clause BSD-License
# shipped with this file and also available at: https://github.com/seqan/raptor/blob/main/LICENSE.md
# --------------------------------------------------------------------------------------------------

cmake_minimum_required (VERSION 3.21)

include (FindPackageMessage)

# Uses `ccache` to cache build results.
#
# See also
# * https://ccache.dev/
# * https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_LAUNCHER.html
macro (require_ccache)
    option (USE_CCACHE "Use ccache if available." ON)
    set (FPROFILE_ABS_PATH "-fprofile-abs-path")
    if (USE_CCACHE)
        find_program (CCACHE_PROGRAM ccache)

        if (NOT CCACHE_PROGRAM)
            find_package_message (CCACHE_PROGRAM "  Ccache program:             not available" "[${CCACHE_PROGRAM}]")
        else ()
            find_package_message (CCACHE_PROGRAM "  Ccache program:             available" "[${CCACHE_PROGRAM}]")
            set (FPROFILE_ABS_PATH "--ccache-skip -fprofile-abs-path")

            list (PREPEND CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
            list (PREPEND CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")

            list (PREPEND CMAKE_CXX_LINKER_LAUNCHER "${CCACHE_PROGRAM}")
            list (PREPEND CMAKE_C_LINKER_LAUNCHER "${CCACHE_PROGRAM}")
        endif ()

        unset (CCACHE_PROGRAM)
    endif ()
endmacro ()
