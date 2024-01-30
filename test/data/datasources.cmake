# SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: CC0-1.0

cmake_minimum_required (VERSION 3.16)

include (cmake/app_datasources.cmake)

# copies file to <build>/data/in.fastq
declare_datasource (FILE in.fastq URL ${CMAKE_SOURCE_DIR}/test/data/in.fastq URL_HASH
                    SHA256=6e30fc35f908a36fe0c68a7a35c47f51f9570da16622fb0c072a20e6a9ba5b3e
)
declare_datasource (FILE out.fasta URL ${CMAKE_SOURCE_DIR}/test/data/out.fasta URL_HASH
                    SHA256=2c1ccd1b391c45cbbe1b4448584106d2ad2dc996a1636dcfd67342b7f943116a
)
