// SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0

#include <cstdint>
#include <filesystem>

#include <sharg/all.hpp>

#include <seqan3/search/views/kmer_hash.hpp>

#include "index.hpp"
#include "sequence_io.hpp"

//!\brief A struct that stores the configuration of the search command.
struct search_config
{
    //!\brief The index that should be used for the search.
    std::filesystem::path index{};
    //!\brief The input file that contains the sequences that should be searched.
    std::filesystem::path query{};
    //!\brief The output file where the search results should be stored.
    std::filesystem::path output{};
    //!\brief When a query sequence has more than this fraction of k-mers in a user bin, the user bin is reported.
    double threshold{0.7};
};

//!\brief Searches the k-mers in the query sequences using the given index and stores the results in the output file.
void search_index(search_config const & config)
{
    // TODO: Remove the following line:
    (void)config; // Suppresses unused variable warning.

    // TODO: Load the index from the given file.

    // TODO:
    // * Create a membership_agent for the hibf.
    // * Open the input file for reading IDs and sequences of the queries.
    // * Open the output file for writing the results.
    // * Create a std::vector that we use for storing the k-mer hashes.

    // TODO OPTIONAL: The membership_agent will return the user bin IDs.
    // It would be helpful to have some kind of header that tells us which user bin ID corresponds to which file.
    // E.g.:
    // #0 /path/to/user_bin_0.fasta
    // #1 /path/to/user_bin_1.fasta
    // etc.

    // TODO:
    // * For each query sequence, calculate the k-mer hashes and determine in which user bins they occur.
    // * Write the results to the output file: "<ID>\t<list of user bin ids separated by space>\n"
    // HINT:
    // * You can copy the elements of a view into a vector: `vector.assign(view.begin(), view.end())`.
    // OPTIONAL:
    // * Sort the user bin IDs before writing them to the output file.
}

//!\brief Parses the command line arguments and searches the k-mers in the query sequences using the given index.
void search(sharg::parser & parser)
{
    search_config config{};
    parser.add_option(config.index,
                      sharg::config{.short_id = 'i',
                                    .long_id = "index",
                                    .description = "The index to search the k-mers in.",
                                    .required = true,
                                    .validator = sharg::input_file_validator{}});

    parser.add_option(config.query,
                      sharg::config{.short_id = 'q',
                                    .long_id = "query",
                                    .description = "The input file containing the sequences that should be searched.",
                                    .required = true,
                                    .validator = sharg::input_file_validator{{"fq", "fastq"}}});

    parser.add_option(config.output,
                      sharg::config{.short_id = 'o',
                                    .long_id = "output",
                                    .description = "The output file where the search results should be stored.",
                                    .required = true,
                                    .validator = sharg::output_file_validator{}});

    parser.add_option(config.threshold,
                      sharg::config{.short_id = '\0',
                                    .long_id = "threshold",
                                    .description = "Only report user bins where more than this fraction of all k-mers "
                                                   "in a query sequence are found.",
                                    .validator = sharg::arithmetic_range_validator{0.0, 1.0}});

    try
    {
        parser.parse();
    }
    catch (sharg::parser_error const & ext)
    {
        std::cerr << "Parsing error. " << ext.what() << '\n';
        std::exit(EXIT_FAILURE);
    }

    search_index(config);
}
