#ifndef HAND_H
#define HAND_H

#include "card.h"
#include <memory>
#include <vector>

class Hand {
private:
    int _n_cards = 0;
    std::vector<std::unique_ptr<Card>> _hand;

public:
    Hand();
    // ~Hand();
    void Deal(std::unique_ptr<Card> card);
    friend std::ostream &operator<<(std::ostream &os, const Hand &hand);
};

#endif /* HAND_H */