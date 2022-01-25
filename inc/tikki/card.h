#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <type_traits>

class Card {
private:
    const int _rank;
    const int _suit;

public:
    Card(const int suit, const int rank);
    friend std::ostream &operator<<(std::ostream &os, const Card &card);
};

#endif /* CARD_H */
