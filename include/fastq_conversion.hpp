// SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0

#pragma once

#include "configuration.hpp"

/*! \brief Function, converting fastq files to fasta files.
 *  \param config The configuration.
 *
 *  Simple function, converting fastq files to fasta files using the seqan3 library.
 *  For more information about the SeqAn Library functions see https://docs.seqan.de/seqan3/main_user.
 */
void convert_fastq(configuration const & config);
