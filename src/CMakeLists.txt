# SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: CC0-1.0

cmake_minimum_required (VERSION 3.16)

# A interface to reuse common properties.
# You can add more external include paths of other projects that are needed for your project.
add_library ("${PROJECT_NAME}_interface" INTERFACE)
target_link_libraries ("${PROJECT_NAME}_interface" INTERFACE seqan3::seqan3)
target_link_libraries ("${PROJECT_NAME}_interface" INTERFACE sharg::sharg)
target_link_libraries ("${PROJECT_NAME}_interface" INTERFACE seqan::hibf)
target_include_directories ("${PROJECT_NAME}_interface" INTERFACE "${CMAKE_CURRENT_LIST_DIR}/../include")
target_compile_options ("${PROJECT_NAME}_interface" INTERFACE "-pedantic" "-Wall" "-Wextra")

# An object library (without main) to be used in multiple targets.
add_library ("${PROJECT_NAME}_lib" STATIC fastq_conversion.cpp)
target_link_libraries ("${PROJECT_NAME}_lib" PUBLIC "${PROJECT_NAME}_interface")

add_executable ("${PROJECT_NAME}" main.cpp)
target_link_libraries ("${PROJECT_NAME}" PRIVATE "${PROJECT_NAME}_lib")
