#pragma once

#include <filesystem>

struct configuration
{
    std::filesystem::path fastq_input{};
    std::filesystem::path fasta_output{};
    bool verbose{}; // Default is false.
};
