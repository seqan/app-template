#pragma once

#include "configuration.hpp"

/*! \brief Function, converting fastq files to fasta files.
 *  \param config The configuration.
 *
 *  Simple function, converting fastq files to fasta files using the seqan3 library.
 *  For more information about the SeqAn Library functions see https://docs.seqan.de/seqan3/main_user.
 */
void convert_fastq(configuration const & config);
