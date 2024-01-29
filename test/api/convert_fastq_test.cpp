#include <gtest/gtest.h>

#include <seqan3/test/tmp_directory.hpp>

#include "../cli/cli_test.hpp" // For cli_test::data and cli_test::string_from_file.
#include "fastq_conversion.hpp"

TEST(convert_fastq, out_empty)
{
    std::string_view const expected{">seq1\nACGTTTGATTCGCG\n>seq2\nTCGGGGGATTCGCG\n"};

    testing::internal::CaptureStdout();
    convert_fastq(cli_test::data("in.fastq"), "");
    std::string const std_cout = testing::internal::GetCapturedStdout();

    EXPECT_EQ(expected, std_cout);
}

TEST(convert_fastq, out_not_empty)
{
    // Creates a temporary directory and deletes it after the test.
    seqan3::test::tmp_directory const tmp_dir{};

    std::filesystem::path const test_output = tmp_dir.path() / "out.fasta";
    convert_fastq(cli_test::data("in.fastq"), test_output); // create out.fasta

    ASSERT_TRUE(std::filesystem::exists(test_output)); // check whether out.fasta exists

    // Check whether out.fasta is correct
    std::string const expected = cli_test::string_from_file(cli_test::data("out.fasta"));
    std::string const actual = cli_test::string_from_file(test_output);
    EXPECT_EQ(actual, expected);
}
