#ifndef BOTPLAYER_H
#define BOTPLAYER_H

#include "Player.h"
#include <random>

class BotPlayer : public Player {
public:
    explicit BotPlayer(const std::string& name);

    int chooseCardIndex(const std::vector<PlayedCard>& round,
        bool hasLeadSuit, int leadSuit,
        const std::vector<int>& legal) override;

private:
    std::mt19937 rng_;
};

#endif
