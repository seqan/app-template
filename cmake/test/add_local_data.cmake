# SPDX-FileCopyrightText: 2006-2025 Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2025 Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: CC0-1.0

set (DATASOURCES_DATA_DIR "${${PROJECT_NAME}_SOURCE_DIR}/test/data")

file (GLOB_RECURSE datasources
      LIST_DIRECTORIES false
      RELATIVE ${DATASOURCES_DATA_DIR}
      CONFIGURE_DEPENDS ${DATASOURCES_DATA_DIR}/*
)
list (REMOVE_ITEM datasources datasources.cmake README.md REUSE.toml)
list (FILTER datasources EXCLUDE REGEX "\.license")

foreach (datasource IN LISTS datasources)
    get_filename_component (datasource_name "${datasource}" NAME)
    set (data_dir "${CMAKE_CURRENT_BINARY_DIR}/data")
    file (MAKE_DIRECTORY "${data_dir}")

    # You can replace the `if (FALSE)` with a condition to check the file type:
    # if (datasource_name MATCHES ".*\.txt$")
    # If a matching file contains `@data_dir@`, it will be replaced with the actual data directory.
    # This is useful if you have test files that need to reference the data directory, e.g., a file containing
    # paths to other files.
    if (FALSE)
        configure_file ("${DATASOURCES_DATA_DIR}/${datasource}" "${data_dir}/${datasource_name}")
    else ()
        configure_file ("${DATASOURCES_DATA_DIR}/${datasource}" "${data_dir}/${datasource_name}" COPYONLY)
    endif ()
endforeach ()
