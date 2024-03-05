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

//!\brief A struct that stores the configuration of the build command.
struct build_config
{
    //!\brief The input file that contains the paths to the files that should be indexed.
    std::filesystem::path input{};
    //!\brief The output file where the index should be stored.
    std::filesystem::path output{};
    //!\brief The paths to the files that should be indexed.
    std::vector<std::filesystem::path> input_files{};
    //!\brief The kmer size that should be used for the index.
    uint8_t kmer{};
    //!\brief The number of threads that should be used for the index construction.
    uint8_t threads{1u};
};

//!\brief Builds an index from the input files and stores it in the output file.
void build_hibf(build_config & config)
{
    // This lambda function will be used for `.input_fn` of the config.
    auto input_lambda = [&config](size_t const user_bin_index, seqan::hibf::insert_iterator it)
    {
        // TODO: Remove the following two lines:
        (void)user_bin_index; // Suppresses unused variable warning.
        (void)it;             // Suppresses unused variable warning.

        // TODO: Read the sequence from the `user_bin_index`-th input file and assign all k-mers to `it`.
    };

    // TODO: Remove the following line:
    (void)input_lambda; // Suppresses unused variable warning.

    // TODO: Create a seqan::hibf::config.

    // TODO: Create a seqan::hibf::hierarchical_interleaved_bloom_filter.

    // TODO: Create a myindex.

    // TODO: Store the myindex in the output file.
}

//!\brief Reads the input files from the input file and stores them in the config.
void read_input_files(build_config & config)
{
    std::ifstream file{config.input};
    std::string line{};

    while (std::getline(file, line))
        config.input_files.emplace_back(line);

    if (config.input_files.empty())
        throw sharg::validation_error{"No input files found in " + config.input.string() + "."};

    std::ranges::for_each(config.input_files, sharg::input_file_validator{{"fa", "fasta"}});
}

//!\brief Adds the options to the parser and calls the build function.
void build(sharg::parser & parser)
{
    build_config config{};
    parser.add_option(config.input,
                      sharg::config{.short_id = 'i',
                                    .long_id = "input",
                                    .description = "Path to a file containing the paths to the files that should be "
                                                   "indexed. The file must contain one path per line.",
                                    .required = true,
                                    .validator = sharg::input_file_validator{}});

    parser.add_option(config.output,
                      sharg::config{.short_id = 'o',
                                    .long_id = "output",
                                    .description = "Output path where the index should be stored.",
                                    .required = true,
                                    .validator = sharg::output_file_validator{}});

    parser.add_option(config.kmer,
                      sharg::config{.short_id = 'k',
                                    .long_id = "kmer",
                                    .description = "The kmer size that should be used for the index.",
                                    .required = true,
                                    .validator = sharg::arithmetic_range_validator{1, 32}});

    parser.add_option(config.threads,
                      sharg::config{.short_id = 't',
                                    .long_id = "threads",
                                    .description = "The number of threads that should be used for the index "
                                                   "construction.",
                                    .validator = positive_integer_validator<decltype(config.threads)>{}});

    try
    {
        parser.parse();
        read_input_files(config);
    }
    catch (sharg::parser_error const & ext)
    {
        std::cerr << "Parsing error. " << ext.what() << '\n';
        std::exit(EXIT_FAILURE);
    }

    build_hibf(config);
}
