// SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0

#include "app_test.hpp"

// To prevent issues when running multiple CLI tests in parallel, give each CLI test unique names:
struct fastq_to_fasta : public app_test
{};

TEST_F(fastq_to_fasta, no_options)
{
    app_test_result const result = execute_app();
    std::string_view const expected{"Fastq-to-Fasta-Converter\n"
                                    "========================\n"
                                    "    Try -h or --help for more information.\n"};

    EXPECT_SUCCESS(result);
    EXPECT_EQ(result.out, expected);
    EXPECT_EQ(result.err, "");
}

TEST_F(fastq_to_fasta, fail_no_argument)
{
    app_test_result const result = execute_app("-v");
    std::string_view const expected{"Parsing error. Not enough positional arguments provided (Need at least 1). "
                                    "See -h/--help for more information.\n"};

    EXPECT_FAILURE(result);
    EXPECT_EQ(result.out, "");
    EXPECT_EQ(result.err, expected);
}

TEST_F(fastq_to_fasta, with_argument)
{
    app_test_result const result = execute_app(data("in.fastq"));

    EXPECT_SUCCESS(result);
    EXPECT_EQ(result.out, ">seq1\nACGTTTGATTCGCG\n>seq2\nTCGGGGGATTCGCG\n");
    EXPECT_EQ(result.err, "");
}

TEST_F(fastq_to_fasta, with_argument_verbose)
{
    app_test_result const result = execute_app(data("in.fastq"), "-v");

    EXPECT_SUCCESS(result);
    EXPECT_EQ(result.out, ">seq1\nACGTTTGATTCGCG\n>seq2\nTCGGGGGATTCGCG\n");
    EXPECT_EQ(result.err, "Conversion was a success. Congrats!\n");
}

TEST_F(fastq_to_fasta, with_out_file)
{
    app_test_result const result = execute_app(data("in.fastq"), "-o", "out.fasta");
    std::string const expected = string_from_file(data("out.fasta"));
    ASSERT_TRUE(std::filesystem::exists("out.fasta")); // check whether out.fasta exists
    std::string const actual = string_from_file("out.fasta");

    EXPECT_SUCCESS(result);
    EXPECT_EQ(result.out, "");
    EXPECT_EQ(result.err, "");
    EXPECT_EQ(actual, expected);
}

TEST_F(fastq_to_fasta, missing_path)
{
    app_test_result const result = execute_app(data("in.fastq"), "-o", "");

    EXPECT_FAILURE(result);
    EXPECT_EQ(result.out, "");
    EXPECT_EQ(result.err, "Parsing error. Missing value for option -o\n");
}

TEST_F(fastq_to_fasta, invalid_path)
{
    app_test_result const result = execute_app(data("in.fastq"), "-o", "does_not_exist/out.fasta");

    EXPECT_FAILURE(result);
    EXPECT_EQ(result.out, "");
    EXPECT_EQ(result.err,
              "Parsing error. Validation failed for option -o/--output: Cannot write \"does_not_exist/out.fasta\"!\n");
}
