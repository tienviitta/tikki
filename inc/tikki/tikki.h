#ifndef TIKKI_H
#define TIKKI_H

#include "deck.h"
#include "hand.h"

#include <vector>

class Tikki {
private:
    int _n_players;
    Deck _deck;
    std::vector<std::unique_ptr<Hand>> _hands;

public:
    Tikki(int n_players);
    void Game();
    void Deal();
    void Play();
};

#endif /* TIKKI_H */