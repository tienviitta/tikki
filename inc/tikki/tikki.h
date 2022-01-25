#ifndef TIKKI_H
#define TIKKI_H

#include "deck.h"

class Tikki {
private:
    int _n_players;
    Deck _deck;

public:
    Tikki(int n_players);
    // ~Tikki();
    void Play();
};

#endif /* TIKKI_H */