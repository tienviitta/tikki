#include "card.h"
#include "spdlog/spdlog.h"

Card::Card(const int suit, const int rank) : _suit(suit), _rank(rank) {
    spdlog::debug("  Card Constructor [{}, {}]", _rank, _suit);
}

std::ostream &operator<<(std::ostream &os, const Card &card) {
    os << "[" << card._suit << ", " << card._rank << "]";
    return os;
}
