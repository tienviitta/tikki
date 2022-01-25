#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <type_traits>

class Card {
private:
    int _rank;
    int _suit;

public:
    Card();
    Card(const int suit, const int rank);
    ~Card();
    // Card(Card const &other);
    // Card &operator=(Card const &other) noexcept;
    // Card(Card &&other);
    // Card &operator=(Card &&other);
    friend std::ostream &operator<<(std::ostream &os, const Card &card);
};

#endif /* CARD_H */
