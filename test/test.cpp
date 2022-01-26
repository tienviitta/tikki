#include "card.h"
#include "deck.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Deck", "[deck]") {

    Deck deck;
    std::unique_ptr<Card> card;

    SECTION("Deal card") {
        card = deck.Deal();
        REQUIRE(card != nullptr);
    }

    SECTION("Put card back") {
        deck.Back(std::move(card));
        REQUIRE(card == nullptr);
    }
}
