// SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0

#include <cstdint>
#include <filesystem>

#include <sharg/all.hpp>

#include <seqan3/search/views/kmer_hash.hpp>

#include "index.hpp"
#include "sequence_io.hpp"
#include "validator.hpp"

//!\brief A struct that stores the configuration of the count command.
struct count_config
{
    //!\brief The index that should be used for the counting.
    std::filesystem::path index{};
    //!\brief The input file that contains the sequences that should be counted.
    std::filesystem::path query{};
    //!\brief The output file where the counts should be stored.
    std::filesystem::path output{};
    //!\brief If a count is below this threshold, it is not reported.
    uint16_t threshold{1u};
};

//!\brief Counts the k-mers in the query sequences using the given index and stores the counts in the output file.
void count_index(count_config const & config)
{
    // TODO: Remove the following line:
    (void)config; // Suppresses unused variable warning.

    // TODO: Load the index from the given file.

    // TODO:
    // * Create a counting_agent for the hibf.
    // * Open the input file for reading IDs and sequences of the queries.
    // * Open the output file for writing the results.
    // * Create a std::vector that we use for storing the k-mer hashes.

    // TODO OPTIONAL: The counting_agent will a count for each user bin.
    // It would be helpful to have some kind of header that tells us which user bin ID corresponds to which file.
    // E.g.:
    // #0 /path/to/user_bin_0.fasta
    // #1 /path/to/user_bin_1.fasta
    // etc.

    // TODO:
    // * For each query sequence, calculate the k-mer hashes and determine the k-mer count in each user bin.
    // * Write the results to the output file: "<ID>\t<count for each user bin separated by space>\n"
    // HINT:
    // * You can copy the elements of a view into a vector: `vector.assign(view.begin(), view.end())`.
}

//!\brief Parses the command line arguments and counts the k-mers in the query sequences using the given index.
void count(sharg::parser & parser)
{
    count_config config{};
    parser.add_option(config.index,
                      sharg::config{.short_id = 'i',
                                    .long_id = "index",
                                    .description = "The index to count the k-mers in.",
                                    .required = true,
                                    .validator = sharg::input_file_validator{}});

    parser.add_option(config.query,
                      sharg::config{.short_id = 'q',
                                    .long_id = "query",
                                    .description = "The input file that contains the sequences that should be counted.",
                                    .required = true,
                                    .validator = sharg::input_file_validator{{"fq", "fastq"}}});

    parser.add_option(config.output,
                      sharg::config{.short_id = 'o',
                                    .long_id = "output",
                                    .description = "The output file where the counts should be stored.",
                                    .required = true,
                                    .validator = sharg::output_file_validator{}});

    parser.add_option(config.threshold,
                      sharg::config{.short_id = '\0',
                                    .long_id = "threshold",
                                    .description = "Only report counts greather than or equal to this value.",
                                    .validator = positive_integer_validator<decltype(config.threshold)>{}});

    try
    {
        parser.parse();
    }
    catch (sharg::parser_error const & ext)
    {
        std::cerr << "Parsing error. " << ext.what() << '\n';
        std::exit(EXIT_FAILURE);
    }

    count_index(config);
}
