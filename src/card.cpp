#include "card.h"
#include "spdlog/spdlog.h"

Card::Card(const int suit, const int rank) : _suit(suit), _rank(rank) {
    spdlog::debug("  Card Constructor {}{}", _rank, _suit);
}
