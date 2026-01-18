#include "Game.h"
#include "HumanPlayer.h"
#include "BotPlayer.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>

Game::Game() : targetScore_(41) {}

int Game::askInt(const std::string& prompt, int lo, int hi) {
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        try {
            int v = std::stoi(line);
            if (v >= lo && v <= hi) return v;
        }
        catch (...) {}
    }
}

void Game::setupPlayers(int nPlayers) {
    players_.clear();

    std::cout << "Unesi svoje ime: ";
    std::string myName;
    std::getline(std::cin, myName);
    if (myName.empty()) myName = "Igrac";

    players_.push_back(std::unique_ptr<Player>(new HumanPlayer(myName)));
    for (int i = 1; i < nPlayers; ++i) {
        players_.push_back(std::unique_ptr<Player>(new BotPlayer("Bot" + std::to_string(i))));
    }

    if (nPlayers == 4) {
        std::cout << "\nMod 4 igraca: ti + 3 bota.\n\n";
    }
    else {
        std::cout << "\nMod 3 igraca: spil od 36 (bez cetvorki), 12 rundi.\n\n";
    }
}

void Game::deal(Deck& deck, int dealer, int cardsPerPlayer) {
    for (size_t i = 0; i < players_.size(); ++i) players_[i]->clearHand();

    for (int i = 0; i < cardsPerPlayer; ++i) {
        for (int p = 1; p <= (int)players_.size(); ++p) {
            int idx = (dealer + p) % (int)players_.size();
            players_[idx]->giveCard(deck.draw());
        }
    }
    for (size_t i = 0; i < players_.size(); ++i) players_[i]->sortHand();
}

int Game::determineRoundWinner(const std::vector<PlayedCard>& round) const {
    int leadSuit = round[0].card().suit();
    int bestPlayer = round[0].playerIndex();
    int bestStrength = Card::roundStrength(round[0].card().rank());

    for (size_t i = 1; i < round.size(); ++i) {
        if (round[i].card().suit() != leadSuit) continue;
        int st = Card::roundStrength(round[i].card().rank());
        if (st > bestStrength) {
            bestStrength = st;
            bestPlayer = round[i].playerIndex();
        }
    }
    return bestPlayer;
}

RoundResult Game::playRound(int leader) {
    std::vector<PlayedCard> round;
    round.reserve(players_.size());

    bool hasLeadSuit = false;
    int leadSuit = Card::Kupe;

    for (int offset = 0; offset < (int)players_.size(); ++offset) {
        int pIdx = (leader + offset) % (int)players_.size();
        Player& p = *players_[pIdx];

        clearConsole();
        std::cout << "Na potezu: " << p.name() << "\n\n";
        if (!round.empty()) {
            std::cout << "Dosad:\n";
            for (size_t i = 0; i < round.size(); ++i) {
                std::cout << "  " << players_[round[i].playerIndex()]->name()
                    << " -> " << round[i].card().toString() << "\n";
            }
            std::cout << "\n";
        }

        if (!hasLeadSuit && !round.empty()) {
            hasLeadSuit = true;
            leadSuit = round[0].card().suit();
        }

        std::vector<int> legal = p.legalMoves(hasLeadSuit, leadSuit);
        int chosenIdx = p.chooseCardIndex(round, hasLeadSuit, leadSuit, legal);
        Card played = p.playIndex(chosenIdx);

        if (!hasLeadSuit) {
            hasLeadSuit = true;
            leadSuit = played.suit();
        }

        round.push_back(PlayedCard(pIdx, played));
    }

    int winner = determineRoundWinner(round);
    return RoundResult(winner, round);
}

void Game::run() {
    clearConsole();

    int nPlayers = askInt("Odaberi broj igraca (3 ili 4): ", 3, 4);
    bool use36 = (nPlayers == 3);
    int cardsPerPlayer = use36 ? 12 : 10;

    setupPlayers(nPlayers);
    targetScore_ = askInt("Igra se do koliko punata? (preporuka 41): ", 1, 200);

    int dealer = 0;
    std::vector<int> totalScore(nPlayers, 0);

    while (true) {
        Deck deck(use36);
        deck.shuffle();
        deal(deck, dealer, cardsPerPlayer);

        clearConsole();
        std::cout << "Ruka pocinje. " << players_[dealer]->name() << "\n\n";

        std::vector<int> akuza(nPlayers, 0);
        for (int i = 0; i < nPlayers; ++i) {
            std::vector<std::string> desc;
            akuza[i] = players_[i]->computeAkuzaPoints(desc);
            if (akuza[i] > 0) {
                std::cout << players_[i]->name() << " akuza +" << akuza[i] << ":\n";
                for (size_t k = 0; k < desc.size(); ++k) std::cout << "   " << desc[k] << "\n";
                std::cout << "\n";
            }
        }
        pauseAndClear();

        int leader = (dealer + 1) % nPlayers;
        std::vector<int> wonThirds(nPlayers, 0);
        int lastRoundWinner = -1;

        for (int t = 0; t < cardsPerPlayer; ++t) {
            RoundResult tr = playRound(leader);
            leader = tr.winnerIndex();
            lastRoundWinner = tr.winnerIndex();

            const std::vector<PlayedCard>& played = tr.played();
            for (size_t i = 0; i < played.size(); ++i) {
                wonThirds[tr.winnerIndex()] += Card::pointsInThirds(played[i].card().rank());
            }

            clearConsole();
            std::cout << "Runda " << (t + 1) << "/" << cardsPerPlayer << "\n\n";
            for (size_t i = 0; i < played.size(); ++i) {
                std::cout << players_[played[i].playerIndex()]->name()
                    << " -> " << played[i].card().toString() << "\n";
            }
            std::cout << "\nDobio: " << players_[tr.winnerIndex()]->name() << "\n";
            pauseAndClear();
        }

        if (lastRoundWinner >= 0) wonThirds[lastRoundWinner] += 3;

        int totalThirds = std::accumulate(wonThirds.begin(), wonThirds.end(), 0);
        int rem = totalThirds % 3;
        if (rem != 0 && lastRoundWinner >= 0) wonThirds[lastRoundWinner] += (3 - rem);

        std::vector<int> handPoints(nPlayers, 0);
        for (int i = 0; i < nPlayers; ++i) {
            handPoints[i] = (wonThirds[i] / 3) + akuza[i];
            totalScore[i] += handPoints[i];
        }

        clearConsole();
        std::cout << "Ruka zavrsena.\n\n";
        for (int i = 0; i < nPlayers; ++i) {
            std::cout << std::setw(12) << players_[i]->name()
                << "  ruka: +" << handPoints[i]
                << "  ukupno: " << totalScore[i] << "\n";
        }

        int best = *std::max_element(totalScore.begin(), totalScore.end());
        if (best >= targetScore_) {
            std::cout << "\nKraj igre. Pobjednik:\n";
            for (int i = 0; i < nPlayers; ++i) {
                if (totalScore[i] == best) {
                    std::cout << "  " << players_[i]->name() << " (" << totalScore[i] << ")\n";
                }
            }
            break;
        }

        dealer = (dealer + 1) % nPlayers;
        pauseAndClear();
    }
}
