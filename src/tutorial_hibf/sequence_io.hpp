// SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0

#pragma once

#include <seqan3/io/sequence_file/input.hpp>

//!\brief Tells seqan3::sequence_file_input to use dna4 as the sequence alphabet.
struct dna4_traits : seqan3::sequence_file_input_default_traits_dna
{
    using sequence_alphabet = seqan3::dna4;
};

//!\brief This seqan3::sequence_file_input will output only the sequence.
using seq_reader = seqan3::sequence_file_input<dna4_traits, seqan3::fields<seqan3::field::seq>>;
//!\brief This seqan3::sequence_file_input will output id and sequence.
using id_seq_reader = seqan3::sequence_file_input<dna4_traits, seqan3::fields<seqan3::field::id, seqan3::field::seq>>;
