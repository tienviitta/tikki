#include "deck.h"
#include "card.h"

#include <algorithm>
#include <random>

Deck::Deck() {
    for (size_t suit = 0; suit < n_suits; suit++) {
        for (size_t rank = 1; rank < n_ranks + 1; rank++) {
            _deck.emplace_back(std::make_unique<Card>(suit, rank));
        }
    }
}

void Deck::Shuffle() {
    std::random_device rd{};
    auto rng = std::default_random_engine{rd()};
    std::shuffle(std::begin(_deck), std::end(_deck), rng);
}

std::unique_ptr<Card> Deck::Deal() {
    auto card = std::move(_deck.front());
    _deck.pop_front();
    return card;
}

void Deck::Back(std::unique_ptr<Card> card) {
    _deck.emplace_back(std::move(card));
}

std::ostream &operator<<(std::ostream &os, const Deck &deck) {
    for (size_t card = 0; card < deck._deck.size(); card++) {
        os << *deck._deck[card].get();
    }

    return os;
}
