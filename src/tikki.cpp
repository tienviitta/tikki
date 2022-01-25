#include "tikki.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"

Tikki::Tikki(int n_players) : _n_players(n_players) {
    // spdlog::debug("  Tikki Constructor");
    // Make the hands
    for (size_t i = 0; i < _n_players; i++) {
        _hands.emplace_back(std::make_unique<Hand>());
    }
}

// Tikki::~Tikki() {}

void Tikki::Play() {
    // Shuffle deck
    _deck.Shuffle();
    spdlog::debug("  Deck: {}", _deck);
    // Deal cards
    for (size_t i = 0; i < 5; i++) {
        for (size_t player = 0; player < _n_players; player++) {
            auto card = _deck.Deal();
            _hands[player].get()->Deal(std::move(card));
        }
    }
    // Show the hands
    for (size_t player = 0; player < _n_players; player++) {
        spdlog::debug("  Hand: {}", *_hands[player]);
    }
}