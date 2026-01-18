#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include "Player.h"
#include "RoundResult.h"
#include <memory>
#include <vector>
#include <string>

class Game {
public:
    Game();
    void run();

private:
    int askInt(const std::string& prompt, int lo, int hi);
    void setupPlayers(int nPlayers);
    void deal(Deck& deck, int dealer, int cardsPerPlayer);

    int determineRoundWinner(const std::vector<PlayedCard>& round) const;
    RoundResult playRound(int leader);

private:
    std::vector<std::unique_ptr<Player>> players_;
    int targetScore_;
};

#endif
