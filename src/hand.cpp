#include "hand.h"
#include "card.h"
#include "spdlog/spdlog.h"
#include <memory>

Hand::Hand() {
    // spdlog::debug("  Hand Constructor");
}

// Hand::~Hand() { spdlog::debug("  Hand Destructor"); }

void Hand::Deal(std::unique_ptr<Card> card) {
    // spdlog::debug("  Hand Deal");
    _hand.emplace_back(std::move(card));
    _n_cards++;
}

std::ostream &operator<<(std::ostream &os, const Hand &hand) {
    for (size_t card = 0; card < (hand._n_cards); card++) {
        os << *hand._hand[card].get();
    }

    return os;
}
