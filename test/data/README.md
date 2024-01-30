<!--
SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
SPDX-License-Identifier: CC0-1.0
-->

# Data Directory

Store the data here that should be used as input files for the tests.
Large files (>50kb) should not be stored here, but rather fetched from a webserver.
Register each file (from external or internal storage) in the `datasources.cmake` file.
