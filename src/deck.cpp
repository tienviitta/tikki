#include "deck.h"
#include "card.h"
#include "spdlog/spdlog.h"

#include <algorithm>
#include <random>

Deck::Deck() {
    spdlog::debug("  Deck Constructor");
    for (size_t suit = 0; suit < n_suits; suit++) {
        for (size_t rank = 1; rank < n_ranks + 1; rank++) {
            _deck.emplace_back(std::make_unique<Card>(suit, rank));
        }
    }
}

// Deck::~Deck() { spdlog::debug("  Deck Destructor"); }

void Deck::Shuffle() {
    spdlog::debug("  Deck Shuffle");
    unsigned seed = 0x1234567;
    std::shuffle(_deck.begin(), _deck.end(), std::default_random_engine(seed));
}

std::ostream &operator<<(std::ostream &os, const Deck &deck) {
    os << deck.n_suits << ", " << deck.n_ranks << ": ";
    for (size_t card = 0; card < (deck.n_suits * deck.n_ranks); card++) {
        os << *deck._deck[card].get();
    }

    return os;
}
