#include <cereal/archives/binary.hpp>
#include <fmindex-collection/fmindex-collection.h>
#include <seqan3/io/sequence_file/all.hpp>
#include <seqan3/alphabet/views/all.hpp>
#include <sharg/all.hpp>

void index(sharg::parser& parser) {
    auto input_file_name = std::filesystem::path{};
    parser.add_option(input_file_name,
                      sharg::config{.short_id = 'i',
                                    .long_id = "input",
                                    .description = "Path to a sequence input file.",
                                    .required = true,
                                    .validator = sharg::input_file_validator{{"fa", "fasta", "fq", "fastq"}}
                      }
    );

    auto output_file_name = std::filesystem::path{};
    parser.add_option(output_file_name,
                      sharg::config{.short_id = 'o',
                                    .long_id = "output",
                                    .description = "Path to the resulting index.",
                                    .default_message = "Defaults to \"<input_file_name>.index\"."
                      }
    );

    parser.parse();

    // loading our files
    auto input_file = seqan3::sequence_file_input{input_file_name};

    // read reference into memory
    auto references = std::vector<std::vector<uint8_t>>{};
    for (auto& record : input_file) {
        auto view = record.sequence() | seqan3::views::to_rank;
        references.emplace_back(view.begin(), view.end());
    }

    // Create FMIndex
    constexpr size_t Sigma = 5; // AlphabetSize
    using Table = fmindex_collection::occtable::Interleaved_16<Sigma+1>;
    using FMIndex = fmindex_collection::FMIndex<Table>;
    auto index = FMIndex{references, /*samplingRate*/16, /*threadNbr*/1};

    // save index to idsk
    if (output_file_name.empty()) {
        output_file_name = input_file_name.string() + ".index";
    }
    {
        auto ofs     = std::ofstream(output_file_name, std::ios::binary);
        auto archive = cereal::BinaryOutputArchive{ofs};
        archive(index);
    }
}
