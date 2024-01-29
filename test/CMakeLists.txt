cmake_minimum_required (VERSION 3.16)

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

    unset (source_file)
    unset (target)
    unset (test_name)
endmacro ()

# Build tests just before their execution, because they have not been built with "all" target.
# The trick is here to provide a cmake file as a directory property that executes the build command.
file (WRITE "${CMAKE_CURRENT_BINARY_DIR}/build_test_targets.cmake"
      "execute_process (COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target api_test)\n"
      "execute_process (COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target cli_test)\n"
      "execute_process (COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${PROJECT_NAME}_header_test)\n"
)
set_directory_properties (PROPERTIES TEST_INCLUDE_FILE "${CMAKE_CURRENT_BINARY_DIR}/build_test_targets.cmake")
list (APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")

# Fetch data and add the tests.
include (data/datasources.cmake)
add_subdirectory (api)
add_subdirectory (cli)
add_subdirectory (header)
add_subdirectory (coverage)

add_custom_target (unit_test
                   COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target api_test cli_test
                   COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -R \"api/ \|cli/\"
)
add_custom_target (header_test
                   COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${PROJECT_NAME}_header_test
                   COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -R \"header\"
)

message (STATUS "${FontBold}You can run `make test` to build and run tests.${FontReset}")
