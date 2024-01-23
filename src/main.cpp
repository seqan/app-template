#include <sstream>

#include <sharg/all.hpp>

#include "fastq_conversion.hpp"

int main(int argc, char ** argv)
{
    sharg::parser parser{"Fastq-to-Fasta-Converter", argc, argv};

    // Declarations for argument parser
    std::filesystem::path fastq_file{};
    std::filesystem::path output_file{};
    bool verbose = false;

    // Parser
    // Give the parser some infos.
    parser.info.author = "SeqAn-Team";
    parser.info.version = "1.0.0";
    // Takes a fastq file and validates it.
    parser.add_positional_option(fastq_file,
                                 sharg::config{.description = "Please provide a fastq file.",
                                               .validator = sharg::input_file_validator{{"fq", "fastq"}}});
    // Takes an output path, default is printing it to the terminal.
    parser.add_option(output_file,
                      sharg::config{.short_id = 'o',
                                    .long_id = "output",
                                    .description = "The file for fasta output.",
                                    .default_message = "Print to terminal (stdout)",
                                    .validator = sharg::output_file_validator{}});
    // Example for a flag.
    parser.add_flag(
        verbose,
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

    convert_fastq(fastq_file, output_file); // Call fastq to fasta converter.

    if (verbose) // If flag is set.
        std::cerr << "Conversion was a success. Congrats!\n";

    return 0;
}
