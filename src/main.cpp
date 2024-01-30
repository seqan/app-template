// SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0

#include <sharg/all.hpp>

#include "fastq_conversion.hpp"

int main(int argc, char ** argv)
{
    // Configuration
    configuration config{};

    // Parser
    sharg::parser parser{"Fastq-to-Fasta-Converter", argc, argv};

    // General information.
    parser.info.author = "SeqAn-Team";
    parser.info.version = "1.0.0";

    // Positional option: The FASTQ file to convert.
    parser.add_positional_option(config.fastq_input,
                                 sharg::config{.description = "The FASTQ file to convert.",
                                               .validator = sharg::input_file_validator{{"fq", "fastq"}}});

    // Open: Output FASTA file. Default: print to terminal - handled in fastq_conversion.cpp.
    parser.add_option(config.fasta_output,
                      sharg::config{.short_id = 'o',
                                    .long_id = "output",
                                    .description = "The output FASTA file.",
                                    .default_message = "Print to terminal (stdout)",
                                    .validator = sharg::output_file_validator{}});

    // Flag: Verose output.
    parser.add_flag(
        config.verbose,
        sharg::config{.short_id = 'v', .long_id = "verbose", .description = "Give more detailed information."});

    try
    {
        parser.parse(); // Trigger command line parsing.
    }
    catch (sharg::parser_error const & ext) // Catch user errors.
    {
        std::cerr << "Parsing error. " << ext.what() << '\n'; // Give error message.
        return -1;
    }

    convert_fastq(config); // Call fastq to fasta converter.

    if (config.verbose) // If flag is set.
        std::cerr << "Conversion was a success. Congrats!\n";

    return 0;
}
