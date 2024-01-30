# SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: CC0-1.0

cmake_minimum_required (VERSION 3.16)

include (seqan3_test_files)
include (seqan3_test_component)

add_library ("${PROJECT_NAME}_header_test_lib" INTERFACE)
target_link_libraries ("${PROJECT_NAME}_header_test_lib" INTERFACE "${PROJECT_NAME}_test")
# SeqAn3 script adds an include for <benchmark/benchmark.h>
file (WRITE "${PROJECT_BINARY_DIR}/dummy_include/benchmark/benchmark.h" "#pragma once")
target_include_directories ("${PROJECT_NAME}_header_test_lib" INTERFACE "${PROJECT_BINARY_DIR}/dummy_include")
set (target "${PROJECT_NAME}_header_test")

set (header_base_path "${CMAKE_CURRENT_LIST_DIR}/../../include/")

file (GLOB_RECURSE header_files
      RELATIVE "${header_base_path}"
      "${header_base_path}/*.hpp"
)

file (WRITE "${PROJECT_BINARY_DIR}/${target}.cpp" "")
add_executable (${target} ${PROJECT_BINARY_DIR}/${target}.cpp)
target_link_libraries (${target} ${PROJECT_NAME}_header_test_lib)
add_test (NAME "${target}" COMMAND ${target})
add_dependencies (check ${target})

foreach (header ${header_files})
    seqan3_test_component (header_test_name "${header}" TEST_NAME)
    seqan3_test_component (header_target_name "${header}" TARGET_UNIQUE_NAME)

    foreach (header_sub_test "header-guard" "no-self-include")
        set (header_target_source
             "${PROJECT_BINARY_DIR}/${target}_files/${header_test_name}.hpp-${header_sub_test}.cpp"
        )
        set (header_target "${target}--${header_target_name}-${header_sub_test}")
        string (REPLACE "-" "__" header_test_name_safe "${target}, ${header_target}")

        # we use add_custom_command to detect changes to a header file, which will update the generated source file
        add_custom_command (OUTPUT "${header_target_source}"
                            COMMAND "${CMAKE_COMMAND}" "-DHEADER_FILE_ABSOLUTE=${header_base_path}/${header}"
                                    "-DHEADER_FILE_INCLUDE=${header}" "-DHEADER_TARGET_SOURCE=${header_target_source}"
                                    "-DHEADER_TEST_NAME_SAFE=${header_test_name_safe}"
                                    "-DHEADER_COMPONENT=${PROJECT_NAME}" "-DHEADER_SUB_TEST=${header_sub_test}" "-P"
                                    "${SEQAN3_CLONE_DIR}/test/header/generate_header_source.cmake"
                            DEPENDS "${header_base_path}/${header}"
                                    "${SEQAN3_CLONE_DIR}/test/header/generate_header_source.cmake"
        )

        add_library (${header_target} OBJECT "${header_target_source}")
        target_link_libraries (${header_target} ${PROJECT_NAME}_header_test_lib)
        target_sources (${target} PRIVATE $<TARGET_OBJECTS:${header_target}>)
    endforeach ()
endforeach ()
