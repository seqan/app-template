cmake_minimum_required (VERSION 3.16)

# Allow to include CMake scripts from seqan3.
list (APPEND CMAKE_MODULE_PATH "${seqan3_SOURCE_DIR}/test/cmake/")
# Allow to include CMake scripts from the app-template.
list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/")

CPMGetSystemPackage (googletest)
include (GoogleTest OPTIONAL)

# Set directories for test output files, input data and binaries.
file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/output)
add_definitions (-DOUTPUTDIR=\"${CMAKE_CURRENT_BINARY_DIR}/output/\")
add_definitions (-DDATADIR=\"${CMAKE_CURRENT_BINARY_DIR}/data/\")
add_definitions (-DBINDIR=\"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/\")

# Test executables and libraries should not mix with the application files.
unset (CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
unset (CMAKE_LIBRARY_OUTPUT_DIRECTORY)
unset (CMAKE_RUNTIME_OUTPUT_DIRECTORY)

include (seqan3_test_component)

add_library (${PROJECT_NAME}_test INTERFACE)
target_compile_options (${PROJECT_NAME}_test INTERFACE "-pedantic" "-Wall" "-Wextra" "-Werror")

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

target_link_libraries (${PROJECT_NAME}_test INTERFACE "${PROJECT_NAME}_lib" "GTest::gtest_main"
)
target_include_directories (${PROJECT_NAME}_test INTERFACE "${seqan3_SOURCE_DIR}/test/include")
add_library (${PROJECT_NAME}::test ALIAS ${PROJECT_NAME}_test)

add_custom_target (check COMMAND ${CMAKE_CTEST_COMMAND})

# A macro that adds an api or cli test.
macro (add_app_test test_filename)
    # Extract the test target name.
    file (RELATIVE_PATH source_file "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_LIST_DIR}/${test_filename}")
    seqan3_test_component (target "${source_file}" TARGET_NAME)
    seqan3_test_component (test_name "${source_file}" TEST_NAME)

    # Create the test target.
    add_executable (${target} ${test_filename})
    target_link_libraries (${target} ${PROJECT_NAME}::test)

    # Generate and set the test name.
    add_test (NAME "${test_name}" COMMAND ${target})
    add_dependencies (check ${target})

    unset (source_file)
    unset (target)
    unset (test_name)
endmacro ()

# Fetch data and add the tests.
include (data/datasources.cmake)

add_custom_target (api_test ALL)

macro (add_api_test test_filename)
    add_app_test (${test_filename})

    seqan3_test_component (target "${test_filename}" TARGET_NAME)
    add_dependencies (api_test ${target})
endmacro ()

add_subdirectory (api)

add_custom_target (cli_test ALL)

macro (add_cli_test test_filename)
    add_app_test (${test_filename})

    seqan3_test_component (target "${test_filename}" TARGET_NAME)
    add_dependencies (cli_test ${target})
    add_dependencies (${target} "${PROJECT_NAME}")
endmacro ()

add_subdirectory (cli)
add_subdirectory (header)
add_subdirectory (coverage)

message (STATUS "${FontBold}You can run `make check` to build and run tests.${FontReset}")
