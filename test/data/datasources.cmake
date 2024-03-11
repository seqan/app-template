# SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: CC0-1.0

include (test/declare_datasource)

# Makes all files in this directory available to the build, i.e., copying them to <build>/data/.
include (test/add_local_data)

# Downloads the to <build>/data/downloaded.fasta
declare_datasource (FILE downloaded.fasta
                    URL https://ftp.seqan.de/app-template/downloaded.fasta
                    URL_HASH SHA256=c3cb990ca1a25c7e31be3c6c2d009238d9ac9a44b2b7c143753c1e2881699077
)
