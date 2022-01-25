#include "hand.h"
#include "card.h"
#include "spdlog/spdlog.h"
#include <memory>

void Hand::Take(std::unique_ptr<Card> card) {
    _hand.emplace_back(std::move(card));
}

std::unique_ptr<Card> Hand::Play() {
    auto card = std::move(_hand.back());
    _hand.pop_back();
    return card;
}

std::ostream &operator<<(std::ostream &os, const Hand &hand) {
    for (size_t card = 0; card < hand._hand.size(); card++) {
        os << *hand._hand[card].get();
    }

    return os;
}
