#include "card.h"

Card::Card(const int suit, const int rank) : _suit(suit), _rank(rank) {}

std::ostream &operator<<(std::ostream &os, const Card &card) {
    os << "[" << card._suit << ", " << card._rank << "], ";
    return os;
}
