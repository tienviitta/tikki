#include "tikki.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"

Tikki::Tikki(int n_players) : _n_players(n_players) {
    for (size_t i = 0; i < _n_players; i++) {
        _hands.emplace_back(std::make_unique<Hand>());
    }
}

void Tikki::Game() {

    // Shuffle deck
    _deck.Shuffle();

    // Show the deck and the hands
    spdlog::debug("  Deck: {}", _deck);
    for (size_t player = 0; player < _n_players; player++) {
        spdlog::debug("  Hand: {}", *_hands[player]);
    }

    // Deal cards
    Deal();

    // Show the deck and the hands
    spdlog::debug("  Deck: {}", _deck);
    for (size_t player = 0; player < _n_players; player++) {
        spdlog::debug("  Hand: {}", *_hands[player]);
    }

    // Play cards
    Play();

    // Show the deck and the hands
    spdlog::debug("  Deck: {}", _deck);
    for (size_t player = 0; player < _n_players; player++) {
        spdlog::debug("  Hand: {}", *_hands[player]);
    }
}

void Tikki::Deal() {
    for (size_t i = 0; i < 5; i++) {
        for (size_t player = 0; player < _n_players; player++) {
            auto card = _deck.Deal();
            _hands[player].get()->Take(std::move(card));
        }
    }
}

void Tikki::Play() {
    for (size_t i = 0; i < 5; i++) {
        for (size_t player = 0; player < _n_players; player++) {
            auto card = _hands[player].get()->Play();
            _deck.Back(std::move(card));
        }
    }
}