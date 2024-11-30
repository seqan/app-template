# SPDX-FileCopyrightText: 2006-2023, Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2023, Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: CC0-1.0

# CPM Package Lock
# This file should be committed to version control

# hibf
set (HIBF_VERSION 28dc84475766aa768c9ed744a1570872361a5ec1)
CPMDeclarePackage (hibf
                   NAME hibf
                   GIT_TAG ${HIBF_VERSION} # main
                   GITHUB_REPOSITORY seqan/hibf
                   SYSTEM TRUE
                   EXCLUDE_FROM_ALL TRUE
                   OPTIONS "INSTALL_HIBF OFF" "CMAKE_MESSAGE_LOG_LEVEL WARNING"
)

# sharg
set (SHARG_VERSION 215da66217957776691b7f8a572cf5a51d368b03)
CPMDeclarePackage (sharg
                   NAME sharg
                   GIT_TAG ${SHARG_VERSION} # main
                   GITHUB_REPOSITORY seqan/sharg-parser
                   SYSTEM TRUE
                   EXCLUDE_FROM_ALL TRUE
                   OPTIONS "INSTALL_SHARG OFF" "INSTALL_TDL OFF" "CMAKE_MESSAGE_LOG_LEVEL WARNING"
)

# seqan3
set (SEQAN3_VERSION f9ba6d63c9130ccdb68a4fc1674cf13289f39a4c)
CPMDeclarePackage (seqan3
                   NAME seqan3
                   GIT_TAG ${SEQAN3_VERSION} # main
                   GITHUB_REPOSITORY seqan/seqan3
                   SYSTEM TRUE
                   EXCLUDE_FROM_ALL TRUE
                   OPTIONS "INSTALL_SEQAN3 OFF" "CMAKE_MESSAGE_LOG_LEVEL WARNING"
)

# fmindex
set (FMINDEX_VERSION a65dd173595d6c633d8333ad36e6796909c38f5a)
CPMDeclarePackage (fmindex
                   NAME fmindex
                   GIT_TAG ${FMINDEX_VERSION} # main
                   GITHUB_REPOSITORY SGSSGene/fmindex-collection
                   SYSTEM TRUE
                   EXCLUDE_FROM_ALL TRUE
                   OPTIONS "CMAKE_MESSAGE_LOG_LEVEL WARNING"
)

# googletest
set (GOOGLETEST_VERSION 1.15.2)
CPMDeclarePackage (googletest
                   NAME GTest
                   VERSION ${GOOGLETEST_VERSION}
                   GITHUB_REPOSITORY google/googletest
                   SYSTEM TRUE
                   EXCLUDE_FROM_ALL TRUE
                   OPTIONS "BUILD_GMOCK OFF" "INSTALL_GTEST OFF" "CMAKE_CXX_STANDARD 20"
                           "CMAKE_MESSAGE_LOG_LEVEL WARNING"
)

# use_ccache
set (USE_CCACHE_VERSION d2a54ef555b6fc2d496a4c9506dbeb7cf899ce37)
CPMDeclarePackage (use_ccache
                   NAME use_ccache
                   GIT_TAG ${USE_CCACHE_VERSION} # main
                   GITHUB_REPOSITORY seqan/cmake-scripts
                   SOURCE_SUBDIR ccache
                   SYSTEM TRUE
                   EXCLUDE_FROM_ALL TRUE
)
