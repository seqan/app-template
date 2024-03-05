// SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0

#include <sharg/all.hpp>

// These are forward declarations of the functions that will be called by the main function.
// They are defined in the files build.cpp, search.cpp, and count.cpp.
void build(sharg::parser &);
void search(sharg::parser &);
void count(sharg::parser &);

int main(int argc, char ** argv)
{
    // The main executable will have three subcommands: build, search, and count.
    sharg::parser parser{"hibf", {argv, argv + argc}, sharg::update_notifications::off, {"build", "search", "count"}};

    try
    {
        parser.parse();
    }
    catch (sharg::parser_error const & ext)
    {
        std::cerr << "Parsing error. " << ext.what() << '\n';
        return -1;
    }

    auto & subparser = parser.get_sub_parser();

    if (subparser.info.app_name == "hibf-build")
    {
        build(subparser);
    }
    else if (subparser.info.app_name == "hibf-search")
    {
        search(subparser);
    }
    else if (subparser.info.app_name == "hibf-count")
    {
        count(subparser);
    }
    else
    {
        std::cerr << "Unknown subcommand: " << subparser.info.app_name << '\n';
        return -1;
    }

    return 0;
}
