#ifndef ROUNDRESULT_H
#define ROUNDRESULT_H

#include "PlayedCard.h"
#include <vector>

class RoundResult {
public:
    RoundResult() : winnerIndex_(-1), played_() {}
    RoundResult(int winnerIndex, const std::vector<PlayedCard>& played)
        : winnerIndex_(winnerIndex), played_(played) {
    }

    int winnerIndex() const { return winnerIndex_; }
    const std::vector<PlayedCard>& played() const { return played_; }

private:
    int winnerIndex_;
    std::vector<PlayedCard> played_;
};

#endif
