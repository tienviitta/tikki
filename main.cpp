#include "cxxopts.hpp"
#include "deck.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"
#include "spdlog/stopwatch.h"
#include "tikki.h"

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
    }

    // Play Tikki
    Tikki tikki(n_players);
    tikki.Play();

    return 0;
}