# SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: CC0-1.0

CPMGetPackage (googletest)

list (APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure") # Must be before `enable_testing ()`.
enable_testing ()

# Set directories for test output files, input data and binaries.
file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/output)
add_definitions (-DOUTPUTDIR=\"${CMAKE_CURRENT_BINARY_DIR}/output/\")
add_definitions (-DDATADIR=\"${CMAKE_CURRENT_BINARY_DIR}/data/\")
add_definitions (-DBINDIR=\"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/\")
add_definitions (-DAPPNAME=\"${PROJECT_NAME}\")

# Add the test interface library.
if (NOT TARGET ${PROJECT_NAME}_test)
    add_library (${PROJECT_NAME}_test INTERFACE)
    target_compile_options (${PROJECT_NAME}_test INTERFACE "-pedantic" "-Wall" "-Wextra")

    # GCC12 and above: Disable warning about std::hardware_destructive_interference_size not being ABI-stable.
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 12)
            target_compile_options (${PROJECT_NAME}_test INTERFACE "-Wno-interference-size")
        endif ()
    endif ()

    # GCC12 has some bogus warnings. They will not be fixed in googletest.
    # https://github.com/google/googletest/issues/4232
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 12 AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13)
            target_compile_options (${PROJECT_NAME}_test INTERFACE "-Wno-restrict")
        endif ()
    endif ()

    target_link_libraries (${PROJECT_NAME}_test INTERFACE "${PROJECT_NAME}_lib" "GTest::gtest_main")
    add_library (${PROJECT_NAME}::test ALIAS ${PROJECT_NAME}_test)
endif ()

# Add the check target that builds and runs tests.
add_custom_target (check COMMAND ${CMAKE_CTEST_COMMAND} ${CMAKE_CTEST_ARGUMENTS})

macro (add_app_test test_filename)
    file (RELATIVE_PATH source_file "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_LIST_DIR}/${test_filename}")
    get_filename_component (target "${source_file}" NAME_WE)

    add_executable (${target} ${test_filename})
    target_link_libraries (${target} ${PROJECT_NAME}::test)

    add_dependencies (${target} ${PROJECT_NAME})
    add_dependencies (check ${target})

    add_test (NAME ${target} COMMAND ${target})

    unset (source_file)
    unset (target)
endmacro ()
