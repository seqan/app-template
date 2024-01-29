cmake_minimum_required (VERSION 3.16)

add_api_test (convert_fastq_test.cpp)
target_use_datasources (convert_fastq_test FILES in.fastq)
