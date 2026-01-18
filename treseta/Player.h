#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include "PlayedCard.h"
#include <string>
#include <vector>

class Player {
public:
    Player(const std::string& name, bool human);
    virtual ~Player();

    const std::string& name() const;
    bool isHuman() const;

    void clearHand();
    void giveCard(const Card& c);
    void sortHand();

    const std::vector<Card>& hand() const;

    std::vector<int> legalMoves(bool hasLeadSuit, int leadSuit) const;

    Card playIndex(int idx);

    int computeAkuzaPoints(std::vector<std::string>& outDescriptions) const;

    virtual int chooseCardIndex(const std::vector<PlayedCard>& round,
        bool hasLeadSuit, int leadSuit,
        const std::vector<int>& legal) = 0;

protected:
    std::string name_;
    bool isHuman_;
    std::vector<Card> hand_;
};

#endif
