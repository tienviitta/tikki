#ifndef CARD_H
#define CARD_H

#include <type_traits>

// enum class Rank : unsigned char {
//     Begin = 0,
//     Ace = 1,
//     Two = 2,
//     Three = 3,
//     Four = 4,
//     Five = 5,
//     Six = 6,
//     Seven = 7,
//     Eight = 8,
//     Nine = 9,
//     Ten = 10,
//     Jack = 11,
//     Queen = 12,
//     King = 13,
//     End = 14
// };

// enum class Suit : unsigned char { Hearts, Diamonds, Clubs, Spades };

class Card {
private:
    const int _rank;
    const int _suit;

public:
    Card(const int suit, const int rank);
};

#endif /* CARD_H */
