# SPDX-FileCopyrightText: 2006-2025, Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2025, Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: CC0-1.0

# CPM Package Lock (https://github.com/cpm-cmake/CPM.cmake)
# This file should be committed to version control

# cmake-format: off

# hibf
set (HIBF_VERSION 5633fc044e93020984ad045c7001ede453b4b9e0 CACHE STRING "" FORCE)
CPMDeclarePackage (hibf
                   NAME hibf
                   GIT_TAG ${HIBF_VERSION} # main
                   GITHUB_REPOSITORY seqan/hibf
                   SYSTEM TRUE
                   EXCLUDE_FROM_ALL TRUE
                   OPTIONS "INSTALL_HIBF OFF" "CMAKE_MESSAGE_LOG_LEVEL WARNING"
)

# sharg
set (SHARG_VERSION dfff01056dda9271b158d34427f2d28fad9f7440 CACHE STRING "" FORCE)
CPMDeclarePackage (sharg
                   NAME sharg
                   GIT_TAG ${SHARG_VERSION} # main
                   GITHUB_REPOSITORY seqan/sharg-parser
                   SYSTEM TRUE
                   EXCLUDE_FROM_ALL TRUE
                   OPTIONS "INSTALL_SHARG OFF" "INSTALL_TDL OFF" "CMAKE_MESSAGE_LOG_LEVEL WARNING" "SHARG_NO_TDL ON"
)

# seqan3
set (SEQAN3_VERSION 7f01aac8985b77b1363e6201316dc636b6d5f16d CACHE STRING "" FORCE)
CPMDeclarePackage (seqan3
                   NAME seqan3
                   GIT_TAG ${SEQAN3_VERSION} # main
                   GITHUB_REPOSITORY seqan/seqan3
                   SYSTEM TRUE
                   EXCLUDE_FROM_ALL TRUE
                   OPTIONS "INSTALL_SEQAN3 OFF" "CMAKE_MESSAGE_LOG_LEVEL WARNING"
)

# fmindex
set (FMINDEX_VERSION c887ee77d62d889dd687c3281fffc99f1aec69e2 CACHE STRING "" FORCE)
CPMDeclarePackage (fmindex
                   NAME fmindex
                   GIT_TAG ${FMINDEX_VERSION} # main
                   GITHUB_REPOSITORY SGSSGene/fmindex-collection
                   SYSTEM TRUE
                   EXCLUDE_FROM_ALL TRUE
                   OPTIONS "CMAKE_MESSAGE_LOG_LEVEL WARNING"
)

# googletest
set (GOOGLETEST_VERSION 1.16.0 CACHE STRING "" FORCE)
CPMDeclarePackage (googletest
                   NAME GTest
                   VERSION ${GOOGLETEST_VERSION}
                   GITHUB_REPOSITORY google/googletest
                   SYSTEM TRUE
                   EXCLUDE_FROM_ALL TRUE
                   OPTIONS "BUILD_GMOCK OFF" "INSTALL_GTEST OFF" "CMAKE_MESSAGE_LOG_LEVEL WARNING"
)

# use_ccache
set (USE_CCACHE_VERSION d2a54ef555b6fc2d496a4c9506dbeb7cf899ce37 CACHE STRING "" FORCE)
CPMDeclarePackage (use_ccache
                   NAME use_ccache
                   GIT_TAG ${USE_CCACHE_VERSION} # main
                   GITHUB_REPOSITORY seqan/cmake-scripts
                   SOURCE_SUBDIR ccache
                   SYSTEM TRUE
                   EXCLUDE_FROM_ALL TRUE
)

# cmake-format: on
