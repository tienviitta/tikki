#include "deck.h"
#include "card.h"
#include "spdlog/spdlog.h"

Deck::Deck() {
    spdlog::debug("  Deck Constructor");
    for (size_t suit = 0; suit < n_suits; suit++) {
        for (size_t rank = 1; rank < n_ranks + 1; rank++) {
            Card *card = new Card(suit, rank);
            _deck.emplace_back(card);
        }
    }
}

Deck::~Deck() {
    spdlog::debug("  Deck Destructor");
    for (auto card : _deck) {
        delete card;
    }
}