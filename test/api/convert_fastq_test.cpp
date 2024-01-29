#include <gtest/gtest.h>

#include <seqan3/test/tmp_directory.hpp>

#include "../cli/cli_test.hpp" // For cli_test::data and cli_test::string_from_file.
#include "fastq_conversion.hpp"

TEST(convert_fastq, out_empty)
{
    std::string_view const expected{">seq1\nACGTTTGATTCGCG\n>seq2\nTCGGGGGATTCGCG\n"};

    testing::internal::CaptureStdout();
    configuration const config{.fastq_input = cli_test::data("in.fastq")};
    convert_fastq(config);
    std::string const std_cout = testing::internal::GetCapturedStdout();

    EXPECT_EQ(expected, std_cout);
}

TEST(convert_fastq, out_not_empty)
{
    // Creates a temporary directory and deletes it after the test.
    seqan3::test::tmp_directory const tmp_dir{};

    std::filesystem::path const test_output = tmp_dir.path() / "out.fasta";
    configuration const config{.fastq_input = cli_test::data("in.fastq"), .fasta_output = test_output};
    convert_fastq(config); // create out.fasta

    ASSERT_TRUE(std::filesystem::exists(test_output)); // check whether out.fasta exists

    // Check whether out.fasta is correct
    std::string const expected = cli_test::string_from_file(cli_test::data("out.fasta"));
    std::string const actual = cli_test::string_from_file(test_output);
    EXPECT_EQ(actual, expected);
}
