#include <gtest/gtest.h>

#include "../app_test.hpp"
#include "fastq_conversion.hpp"

// To prevent issues when running multiple API tests in parallel, give each API test unique names:
struct fastq_to_fasta : public app_test
{};

TEST_F(fastq_to_fasta, out_empty)
{
    std::string_view const expected{">seq1\nACGTTTGATTCGCG\n>seq2\nTCGGGGGATTCGCG\n"};

    testing::internal::CaptureStdout();
    configuration const config{.fastq_input = data("in.fastq")};
    convert_fastq(config);
    std::string const std_cout = testing::internal::GetCapturedStdout();

    EXPECT_EQ(expected, std_cout);
}

TEST_F(fastq_to_fasta, out_not_empty)
{
    std::filesystem::path const test_output = "out.fasta";
    configuration const config{.fastq_input = data("in.fastq"), .fasta_output = test_output};
    convert_fastq(config); // create out.fasta

    ASSERT_TRUE(std::filesystem::exists(test_output)); // check whether out.fasta exists

    // Check whether out.fasta is correct
    std::string const expected = string_from_file(data("out.fasta"));
    std::string const actual = string_from_file(test_output);
    EXPECT_EQ(actual, expected);
}
