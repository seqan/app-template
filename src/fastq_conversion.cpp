// SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0

#include "fastq_conversion.hpp"

#include <seqan3/io/sequence_file/all.hpp>

void convert_fastq(configuration const & config)
{
    seqan3::sequence_file_input file_input{config.fastq_input};
    seqan3::sequence_file_output file_output{std::cout, seqan3::format_fasta{}};
    if (!config.fasta_output.empty())
        file_output = config.fasta_output;

    file_output = file_input; // conversion
}
