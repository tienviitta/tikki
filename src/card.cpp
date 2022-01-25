#include "card.h"
#include "spdlog/spdlog.h"

Card::Card() : _suit(0), _rank(1) {
    // spdlog::debug("  Card Constructor [{}, {}]", _rank, _suit);
}

Card::Card(const int suit, const int rank) : _suit(suit), _rank(rank) {
    // spdlog::debug("  Card Constructor [{}, {}]", _rank, _suit);
}

Card::~Card() {
    // spdlog::debug("  Card Destructor [{}, {}]", _rank, _suit);
}

// Card::Card(Card const &other) : _suit(other._suit), _rank(other._rank) {
//     spdlog::debug("  Card Copy Constructor [{}, {}]", _rank, _suit);
// }

// Card &Card::operator=(Card const &other) noexcept {
//     spdlog::debug("  Card Copy Assignment [{}, {}]", other._rank,
//     other._suit); if (this != &other) {
//         _suit = other._suit;
//         _rank = other._rank;
//     }
//     return *this;
// }

// Card::Card(Card &&other) {
//     spdlog::debug("  Card Move Constructor [{}, {}]", other._rank,
//     other._suit); _suit = other._suit; _rank = other._rank; other._suit = 0;
//     other._rank = 0;
// }

// Card &Card::operator=(Card &&other) {
//     spdlog::debug("  Card Move Assignment [{}, {}]", other._rank,
//     other._suit); if (this != &other) {
//         _suit = other._suit;
//         _rank = other._rank;
//         other._suit = 0;
//         other._rank = 0;
//     }
//     return *this;
// }

std::ostream &operator<<(std::ostream &os, const Card &card) {
    os << "[" << card._suit << ", " << card._rank << "]";
    return os;
}
