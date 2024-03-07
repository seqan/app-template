// SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0

#include <sharg/all.hpp>

void index(sharg::parser&);
void search(sharg::parser&);

int main(int argc, char ** argv) {
    try {
        // Parser
        sharg::parser parser{"fmindex-tool", argc, argv, sharg::update_notifications::off, {"index", "search"}};

        // General information.
        parser.info.author = "SeqAn-Team";
        parser.info.version = "1.0.0";

        parser.parse(); // Trigger command line parsing.

        auto& subparser = parser.get_sub_parser();
        if (subparser.info.app_name == "fmindex-tool-index") {
            index(subparser);
        } else if (subparser.info.app_name == "fmindex-tool-search") {
            search(subparser);
        }
    } catch (std::exception const& e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return -1;
    }

    return 0;
}
