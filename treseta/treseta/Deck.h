#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>
#include <random>

class Deck {
public:
    explicit Deck(bool use36Cards);
    void shuffle();
    Card draw();
    int size() const;

private:
    void build(bool use36Cards);

    std::vector<Card> cards_;
    std::mt19937 rng_;
};

#endif
