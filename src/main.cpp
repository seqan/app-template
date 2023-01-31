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
    parser.info.author = "SeqAn-Team"; // give parser some infos
    parser.info.version = "1.0.0";
    parser.add_positional_option(fastq_file,
                                sharg::config{.description = "Please provide a fastq file.",
                                .validator = sharg::input_file_validator{{"fq","fastq"}}}); // Takes a fastq file and validates it
    //output path as option, otherwise output is printed
    parser.add_option(output_file,
                    sharg::config{.short_id = 'o', .long_id = "output",
                    .description = "The file for fasta output. Default: stdout"});
    parser.add_flag(verbose,
                    sharg::config{.short_id = 'v', .long_id = "verbose",
                    .description = "Give more detailed information here."}); // example for a flag

    try
    {
         parser.parse();                                                  // trigger command line parsing
    }
    catch (sharg::parser_error const & ext)                     // catch user errors
    {
        std::cerr << "Parsing error. " << ext.what() << "\n"; // give error message
        return -1;
    }

    convert_fastq(fastq_file, output_file); // Call fastq to fasta converter

    if (verbose) // if flag is set
        std::cerr << "Conversion was a success. Congrats!\n";

    return 0;
}
