#include "cxxopts.hpp"
#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

int main() {
    spdlog::info("Tikki card game:");
    // Set global log level to debug
    spdlog::set_level(spdlog::level::debug);
    // Set rand seed
    std::srand(0x123456);
    // std::srand(std::time(nullptr));
    std::vector<std::string> msg{"Hello", "C++",     "World",
                                 "from",  "VS Code", "and the C++ extension!"};
    std::vector<int> rands{};
    for (const std::string &word : msg) {
        int uni_rand = std::rand() % 100;
        rands.emplace_back(uni_rand);
        std::cout << word << " ";
    }
    std::cout << std::endl;
    std::stringstream ss_rands;
    std::copy(rands.begin(), rands.end(),
              std::ostream_iterator<int>(ss_rands, ", "));
    spdlog::debug("  rands: [{}]",
                  ss_rands.str().substr(0, ss_rands.str().length() - 2));
}