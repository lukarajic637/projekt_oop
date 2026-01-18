#include "HumanPlayer.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>
#include <cctype>

HumanPlayer::HumanPlayer(const std::string& name)
    : Player(name, true) {
}

int HumanPlayer::chooseCardIndex(const std::vector<PlayedCard>&,
    bool, int,
    const std::vector<int>& legal) {
    while (true) {
        std::cout << "\nTvoj potez. Odaberi kartu (unesi broj):\n\n";

        std::map<int, bool> isLegal;
        for (size_t i = 0; i < legal.size(); ++i) isLegal[legal[i]] = true;

        for (int i = 0; i < (int)hand_.size(); ++i) {
            std::cout << std::setw(2) << i << ") " << hand_[i].toString();
            if (isLegal[i]) std::cout << "  [OK]";
            std::cout << "\n";
        }

        std::cout << "\n> ";
        std::string line;
        std::getline(std::cin, line);

        line.erase(line.begin(), std::find_if(line.begin(), line.end(),
            [](unsigned char ch) { return !std::isspace(ch); }));
        line.erase(std::find_if(line.rbegin(), line.rend(),
            [](unsigned char ch) { return !std::isspace(ch); }).base(), line.end());

        if (line.empty()) continue;

        int choice = -1;
        try { choice = std::stoi(line); }
        catch (...) { continue; }

        if (choice >= 0 && choice < (int)hand_.size() && isLegal[choice]) return choice;
    }
}
