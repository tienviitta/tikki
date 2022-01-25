#include "cxxopts.hpp"
#include "deck.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"
#include "spdlog/stopwatch.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, const char **argv) {
    // Welcome
    spdlog::info("Tikki card game:");

    // Command line arguments
    cxxopts::Options options("Tikki", "Tikki card game");
    // clang-format off
    options.add_options()
        ("d, debug", "Enable debugging")
        ("p, players", "Number of players", cxxopts::value<int>()->default_value("2"))
        ("h, help", "Print usage");
    // clang-format on
    options.allow_unrecognised_options();
    auto result = options.parse(argc, argv);
    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        return 0;
    }
    bool debug = result["debug"].as<bool>();
    int n_players = result["players"].as<int>();

    // Set global log level to debug
    if (debug) {
        spdlog::set_level(spdlog::level::debug);
        std::srand(0x123456);
    } else {
        std::srand(std::time(nullptr));
    }

    // Make a deck
    Deck deck;

    // // Random integers
    // std::vector<int> rands{};
    // for (size_t i = 0; i < 30; i++) {
    //     int uni_rand = std::rand() % (52 - i);
    //     rands.emplace_back(uni_rand);
    // }
    // std::stringstream ss_rands;
    // std::copy(rands.begin(), rands.end(),
    //           std::ostream_iterator<int>(ss_rands, ", "));
    // spdlog::info("  rands: [{}]",
    //              ss_rands.str().substr(0, ss_rands.str().length() - 2));
    return 0;
}