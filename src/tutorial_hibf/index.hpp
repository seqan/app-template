// SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0

#pragma once

#include <hibf/cereal/path.hpp>
#include <hibf/config.hpp>
#include <hibf/hierarchical_interleaved_bloom_filter.hpp>

//!\brief A class that stores the k-mer size, HIBF, the input file paths.
class myindex
{
public:
    //!\brief The k-mer size that was used for the index.
    uint8_t kmer{};
    //!\brief The input files that were used for the index.
    std::vector<std::filesystem::path> input_files{};
    //!\brief The Hierarchical Interleaved Bloom Filter that was constructed from the input files.
    seqan::hibf::hierarchical_interleaved_bloom_filter hibf{};

    myindex() = default;
    myindex & operator=(myindex const &) = default;
    myindex(myindex const &) = default;
    myindex(myindex &&) = default;
    myindex & operator=(myindex &&) = default;
    ~myindex() = default;

    //!\brief Construct a myindex from the given k-mer size, input files, and HIBF.
    explicit myindex(uint8_t const kmer,
                     std::vector<std::filesystem::path> input_files,
                     seqan::hibf::hierarchical_interleaved_bloom_filter hibf) :
        kmer{kmer},
        input_files{std::move(input_files)},
        hibf{std::move(hibf)}
    {}

    //!\brief Store myindex in the given file.
    void store(std::filesystem::path const & path) const
    {
        std::ofstream fout{path};
        cereal::BinaryOutputArchive oarchive{fout};
        oarchive(*this);
    }

    //!\brief Load myindex from the given file.
    void load(std::filesystem::path const & path)
    {
        std::ifstream fin{path};
        cereal::BinaryInputArchive iarchive{fin};
        iarchive(*this);
    }

    //!\brief Tells cereal how to serialize myindex.
    template <typename archive_t>
    void CEREAL_SERIALIZE_FUNCTION_NAME(archive_t & archive)
    {
        archive(kmer);
        archive(input_files);
        archive(hibf);
    }
};
