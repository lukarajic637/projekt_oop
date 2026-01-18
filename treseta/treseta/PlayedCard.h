#ifndef PLAYEDCARD_H
#define PLAYEDCARD_H

#include "Card.h"

class PlayedCard {
public:
    PlayedCard() : playerIndex_(-1), card_() {}
    PlayedCard(int playerIndex, const Card& card) : playerIndex_(playerIndex), card_(card) {}

    int playerIndex() const { return playerIndex_; }
    const Card& card() const { return card_; }

private:
    int playerIndex_;
    Card card_;
};

#endif
