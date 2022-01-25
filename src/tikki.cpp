#include "tikki.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"

Tikki::Tikki(int n_players) : _n_players(n_players) {
    spdlog::debug("  Tikki Constructor");
}

// Tikki::~Tikki() {}

void Tikki::Play() {
    // Make a deck
    Deck deck;
    spdlog::debug("  Deck: {}", deck);
    deck.Shuffle();
    spdlog::debug("  Deck: {}", deck);
}