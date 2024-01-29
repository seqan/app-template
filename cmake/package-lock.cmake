# SPDX-FileCopyrightText: 2006-2023, Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2023, Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: CC0-1.0

# CPM Package Lock
# This file should be committed to version control

# hibf
set (HIBF_VERSION 2075a68d10f571399b5ff885f0b4cb2c94845601)
CPMDeclarePackage (hibf
                   NAME hibf
                   GIT_TAG ${HIBF_VERSION}
                   VERSION 1.0.0 # Pretty-print only
                   GITHUB_REPOSITORY seqan/hibf
                   SYSTEM TRUE
                   OPTIONS "INSTALL_HIBF OFF" "CMAKE_MESSAGE_LOG_LEVEL WARNING"
)
# sharg
set (SHARG_VERSION 3e96d37387125bd876ace3fdd11a20039ed0d21c)
CPMDeclarePackage (sharg
                   NAME sharg
                   GIT_TAG ${SHARG_VERSION}
                   VERSION 1.1.2 # Pretty-print only
                   GITHUB_REPOSITORY seqan/sharg-parser
                   SYSTEM TRUE
                   OPTIONS "INSTALL_SHARG OFF" "INSTALL_TDL OFF" "CMAKE_MESSAGE_LOG_LEVEL WARNING"
)
# seqan3
set (SEQAN3_VERSION ee718d0d3bbf07a894b5208d37ddf71ba5a5bf44)
CPMDeclarePackage (seqan3
                   NAME seqan3
                   GIT_TAG ${SEQAN3_VERSION}
                   VERSION 3.1.2 # Pretty-print only
                   GITHUB_REPOSITORY seqan/seqan3
                   SYSTEM TRUE
                   OPTIONS "INSTALL_SEQAN3 OFF" "CMAKE_MESSAGE_LOG_LEVEL WARNING"
)
# googletest
set (GOOGLETEST_VERSION 1.14.0)
CPMDeclarePackage (googletest
                   NAME GTest
                   VERSION ${GOOGLETEST_VERSION}
                   GITHUB_REPOSITORY google/googletest
                   SYSTEM TRUE
                   OPTIONS "BUILD_GMOCK OFF" "INSTALL_GTEST OFF" "CMAKE_MESSAGE_LOG_LEVEL WARNING"
)
