#ifndef HAND_H
#define HAND_H

#include "card.h"
#include <memory>
#include <vector>

class Hand {
private:
    std::vector<std::unique_ptr<Card>> _hand;

public:
    void Take(std::unique_ptr<Card> card);
    std::unique_ptr<Card> Play();
    friend std::ostream &operator<<(std::ostream &os, const Hand &hand);
};

#endif /* HAND_H */