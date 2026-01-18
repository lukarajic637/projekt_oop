#include "Deck.h"
#include <algorithm>
#include <stdexcept>

Deck::Deck(bool use36Cards) : rng_(std::random_device{}()) {
    build(use36Cards);
}

void Deck::shuffle() {
    std::shuffle(cards_.begin(), cards_.end(), rng_);
}

Card Deck::draw() {
    if (cards_.empty()) throw std::runtime_error("Deck is empty.");
    Card c = cards_.back();
    cards_.pop_back();
    return c;
}

int Deck::size() const {
    return (int)cards_.size();
}

void Deck::build(bool use36Cards) {
    cards_.clear();

    const int suits[4] = { Card::Kupe, Card::Spade, Card::Bastoni, Card::Dinari };
    std::vector<int> ranks;

    ranks.push_back(Card::As);
    ranks.push_back(Card::Dvica);
    ranks.push_back(Card::Trica);
    ranks.push_back(Card::Cetrvorka);
    ranks.push_back(Card::Petica);
    ranks.push_back(Card::Sestica);
    ranks.push_back(Card::Sedmica);
    ranks.push_back(Card::Fanat);
    ranks.push_back(Card::Konj);
    ranks.push_back(Card::Kralj);

    if (use36Cards) {
        ranks.erase(std::remove(ranks.begin(), ranks.end(), Card::Cetrvorka), ranks.end());
    }

    for (int si = 0; si < 4; ++si) {
        for (size_t ri = 0; ri < ranks.size(); ++ri) {
            cards_.push_back(Card(suits[si], ranks[ri]));
        }
    }
}
