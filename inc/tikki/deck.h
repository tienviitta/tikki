#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <memory>
#include <vector>

class Deck {
private:
    const int n_ranks = 13;
    const int n_suits = 4;
    std::vector<std::unique_ptr<Card>> _deck;

public:
    Deck();
    // ~Deck();
    void Shuffle();
    std::unique_ptr<Card> Deal();
    friend std::ostream &operator<<(std::ostream &os, const Deck &deck);
};

#endif /* DECK_H */