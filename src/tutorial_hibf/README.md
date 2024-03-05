<!--
SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
SPDX-License-Identifier: CC0-1.0
-->

# Files for testing

https://ftp.seqan.de/tutorial/hibf/tutorial_files.tar.gz

```
curl https://ftp.seqan.de/tutorial/hibf/tutorial_files.tar.gz -o tutorial_files.tar.gz
tar xf tutorial_files.tar.gz
```

It also contains a script that creates a file that can be used as input for build.<br>
Note: **BEFORE** executing a script you downloaded from somewhere, you should read the file and check what it does.

```
./tutorial_files/get_filenames.sh
```

Input for build: `tutorial_files/filenames.txt`<br>
Query for search/count: `tutorial_files/reads.fastq`

`reads.fastq` contains 1024 queries. Each has a length of `250`.<br>
The reads were simulated with `2` errors from their respective input file.
