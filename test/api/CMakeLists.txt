# SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: CC0-1.0

cmake_minimum_required (VERSION 3.16)

add_app_test (convert_fastq_test.cpp)
target_use_datasources (convert_fastq_test FILES in.fastq)
target_use_datasources (convert_fastq_test FILES out.fasta)
