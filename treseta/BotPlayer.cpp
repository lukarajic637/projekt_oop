#include "BotPlayer.h"
#include <algorithm>
#include <limits>
#include <stdexcept>

BotPlayer::BotPlayer(const std::string& name)
    : Player(name, false), rng_(std::random_device{}()) {
}


int BotPlayer::chooseCardIndex(const std::vector<PlayedCard>& round,
    bool hasLeadSuit, int leadSuit,
    const std::vector<int>& legal)
{
    if (legal.empty()) throw std::runtime_error("No legal moves.");

    auto cardPoints = [&](const Card& c) -> int {
        return Card::pointsInThirds(c.rank());
        };

    auto cardStrength = [&](const Card& c) -> int {
        return Card::roundStrength(c.rank());
        };

    if (round.empty()) {
        int bestIdx = legal[0];
        int bestStr = cardStrength(hand_[bestIdx]);

        for (size_t i = 1; i < legal.size(); ++i) {
            int idx = legal[i];
            int st = cardStrength(hand_[idx]);
            if (st > bestStr) {
                bestStr = st;
                bestIdx = idx;
            }
        }
        return bestIdx;
    }

    int ls = round[0].card().suit();

    int currentBestStrength = -1;
    for (size_t i = 0; i < round.size(); ++i) {
        if (round[i].card().suit() != ls) continue;
        int st = Card::roundStrength(round[i].card().rank()); 
        if (st > currentBestStrength) currentBestStrength = st;
    }


    int roundPts = 0;
    for (size_t i = 0; i < round.size(); ++i) {
        roundPts += Card::pointsInThirds(round[i].card().rank());
    }

    if (roundPts > 0) {
        int winIdx = -1;
        int winStrength = 1000000;

        for (size_t i = 0; i < legal.size(); ++i) {
            int idx = legal[i];
            const Card& c = hand_[idx];

            if (c.suit() != ls) continue;

            int st = cardStrength(c);
            if (st > currentBestStrength && st < winStrength) {
                winStrength = st;
                winIdx = idx;
            }
        }

        if (winIdx != -1) return winIdx;
    }

    int bestIdx = legal[0];
    int bestP = cardPoints(hand_[bestIdx]);
    int bestS = cardStrength(hand_[bestIdx]);

    for (size_t i = 1; i < legal.size(); ++i) {
        int idx = legal[i];
        int p = cardPoints(hand_[idx]);
        int s = cardStrength(hand_[idx]);

        if (p < bestP) {
            bestP = p;
            bestS = s;
            bestIdx = idx;
        }
        else if (p == bestP && s < bestS) {
            bestS = s;
            bestIdx = idx;
        }
    }

    return bestIdx;
}
