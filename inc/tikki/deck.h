#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <deque>
#include <memory>

class Deck {
private:
    const int n_ranks = 13;
    const int n_suits = 4;
    std::deque<std::unique_ptr<Card>> _deck;

public:
    Deck();
    void Shuffle();
    std::unique_ptr<Card> Deal();
    void Back(std::unique_ptr<Card> card);
    friend std::ostream &operator<<(std::ostream &os, const Deck &deck);
};

#endif /* DECK_H */