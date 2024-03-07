#include <cereal/archives/binary.hpp>
#include <fmindex-collection/fmindex-collection.h>
#include <sharg/all.hpp>

void search(sharg::parser& parser) {
    auto query_file_name = std::filesystem::path{};
    parser.add_option(query_file_name,
                      sharg::config{.short_id = 'q',
                                    .long_id = "query",
                                    .description = "Path to sequence file with queries.",
                                    .required = true,
                                    .validator = sharg::input_file_validator{{"fa", "fasta", "fq", "fastq"}}
                      }
    );

    auto index_file_name = std::filesystem::path{};
    parser.add_option(index_file_name,
                      sharg::config{.long_id = "index",
                                    .description = "Path to the index."
                      }
    );

    parser.parse();

    // Load FMIndex
    constexpr size_t Sigma = 5; // AlphabetSize
    using Table = fmindex_collection::occtable::Interleaved_16<Sigma+1>;
    using FMIndex = fmindex_collection::FMIndex<Table>;
    auto index = FMIndex{};
    {
        auto ifs     = std::ifstream(index_file_name, std::ios::binary);
        auto archive = cereal::BinaryInputArchive{ifs};
        archive(index);
    }

    // Search some stuff
    //!TODO
    //1. check out how to load the queries (HINT, see index.cpp)
    //2. check out https://github.com/SGSSGene/fmindex-collection/blob/main/src/easyExample/main.cpp on how to performe a search
}
