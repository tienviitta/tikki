#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>

class Deck {
private:
    const int n_ranks = 13;
    const int n_suits = 4;
    std::vector<Card *> _deck;

public:
    Deck();
    ~Deck();
};

#endif /* DECK_H */