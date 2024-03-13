# SPDX-FileCopyrightText: 2006-2023, Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2023, Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: CC0-1.0

# CPM Package Lock
# This file should be committed to version control

# hibf
set (HIBF_VERSION 894f663c7b77f28cc2b1b8f4252e51c052c49bb2)
CPMDeclarePackage (hibf
                   NAME hibf
                   GIT_TAG ${HIBF_VERSION}
                   GITHUB_REPOSITORY seqan/hibf
                   SYSTEM TRUE
                   EXCLUDE_FROM_ALL TRUE
                   OPTIONS "INSTALL_HIBF OFF" "CMAKE_MESSAGE_LOG_LEVEL WARNING"
)

# sharg
set (SHARG_VERSION 01f848eeb6dbac3d50a718a8ee26bcf695edf5a8)
CPMDeclarePackage (sharg
                   NAME sharg
                   GIT_TAG ${SHARG_VERSION}
                   GITHUB_REPOSITORY seqan/sharg-parser
                   SYSTEM TRUE
                   EXCLUDE_FROM_ALL TRUE
                   OPTIONS "INSTALL_SHARG OFF" "INSTALL_TDL OFF" "CMAKE_MESSAGE_LOG_LEVEL WARNING"
)

# seqan3
set (SEQAN3_VERSION fee3fb8e5976b455e848dd68c57f64fd3f67c3c2)
CPMDeclarePackage (seqan3
                   NAME seqan3
                   GIT_TAG ${SEQAN3_VERSION}
                   GITHUB_REPOSITORY seqan/seqan3
                   SYSTEM TRUE
                   EXCLUDE_FROM_ALL TRUE
                   OPTIONS "INSTALL_SEQAN3 OFF" "CMAKE_MESSAGE_LOG_LEVEL WARNING"
)

# fmindex
set (FMINDEX_VERSION 822d4d1aa6fa725f7d34e1ea819e9c23a2b6ebc2)
CPMDeclarePackage (fmindex
                   NAME fmindex
                   GIT_TAG ${FMINDEX_VERSION}
                   GITHUB_REPOSITORY SGSSGene/fmindex-collection
                   SYSTEM TRUE
                   EXCLUDE_FROM_ALL TRUE
                   OPTIONS "CMAKE_MESSAGE_LOG_LEVEL WARNING"
)

# googletest
set (GOOGLETEST_VERSION 1.14.0)
CPMDeclarePackage (googletest
                   NAME GTest
                   VERSION ${GOOGLETEST_VERSION}
                   GITHUB_REPOSITORY google/googletest
                   SYSTEM TRUE
                   EXCLUDE_FROM_ALL TRUE
                   OPTIONS "BUILD_GMOCK OFF" "INSTALL_GTEST OFF" "CMAKE_MESSAGE_LOG_LEVEL WARNING"
)

# use_ccache
set (USE_CCACHE_VERSION d2a54ef555b6fc2d496a4c9506dbeb7cf899ce37)
CPMDeclarePackage (use_ccache
                   NAME use_ccache
                   GIT_TAG ${USE_CCACHE_VERSION}
                   GITHUB_REPOSITORY seqan/cmake-scripts
                   SOURCE_SUBDIR ccache
                   SYSTEM TRUE
                   EXCLUDE_FROM_ALL TRUE
)
