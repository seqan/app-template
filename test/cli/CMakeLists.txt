cmake_minimum_required (VERSION 3.16)

add_app_test (fastq_to_fasta_options_test.cpp)
target_use_datasources (fastq_to_fasta_options_test FILES in.fastq)
