#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"

class HumanPlayer : public Player {
public:
    explicit HumanPlayer(const std::string& name);

    int chooseCardIndex(const std::vector<PlayedCard>& round,
        bool hasLeadSuit, int leadSuit,
        const std::vector<int>& legal) override;
};

#endif
