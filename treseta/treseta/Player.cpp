#include "Player.h"
#include <algorithm>
#include <stdexcept>

Player::Player(const std::string& name, bool human)
    : name_(name), isHuman_(human) {
}

Player::~Player() {}

const std::string& Player::name() const { return name_; }
bool Player::isHuman() const { return isHuman_; }

void Player::clearHand() { hand_.clear(); }
void Player::giveCard(const Card& c) { hand_.push_back(c); }

void Player::sortHand() {
    std::sort(hand_.begin(), hand_.end(), [](const Card& a, const Card& b) {
        if (a.suit() != b.suit()) return a.suit() < b.suit();
        return Card::roundStrength(a.rank()) > Card::roundStrength(b.rank());
        });
}

const std::vector<Card>& Player::hand() const { return hand_; }

std::vector<int> Player::legalMoves(bool hasLeadSuit, int leadSuit) const {
    std::vector<int> moves;
    moves.reserve(hand_.size());

    if (!hasLeadSuit) {
        for (int i = 0; i < (int)hand_.size(); ++i) moves.push_back(i);
        return moves;
    }

    bool hasSuit = false;
    for (size_t i = 0; i < hand_.size(); ++i) {
        if (hand_[i].suit() == leadSuit) { hasSuit = true; break; }
    }

    for (int i = 0; i < (int)hand_.size(); ++i) {
        if (!hasSuit || hand_[i].suit() == leadSuit) moves.push_back(i);
    }
    return moves;
}

Card Player::playIndex(int idx) {
    if (idx < 0 || idx >= (int)hand_.size()) throw std::runtime_error("Invalid card index.");
    Card c = hand_[idx];
    hand_.erase(hand_.begin() + idx);
    return c;
}

int Player::computeAkuzaPoints(std::vector<std::string>& outDescriptions) const {
    outDescriptions.clear();

    auto countRank = [&](int r) -> int {
        int cnt = 0;
        for (size_t i = 0; i < hand_.size(); ++i) if (hand_[i].rank() == r) ++cnt;
        return cnt;
        };

    int acc = 0;


    int c3 = countRank(Card::Trica);
    if (c3 == 3) { acc += 3; outDescriptions.push_back("3 trice = 3"); }
    if (c3 == 4) { acc += 4; outDescriptions.push_back("4 trice = 4"); }

    int c2 = countRank(Card::Dvica);
    if (c2 == 3) { acc += 3; outDescriptions.push_back("3 duje = 3"); }
    if (c2 == 4) { acc += 4; outDescriptions.push_back("4 duje = 4"); }

    int cA = countRank(Card::As);
    if (cA == 3) { acc += 3; outDescriptions.push_back("3 asa = 3"); }
    if (cA == 4) { acc += 4; outDescriptions.push_back("4 asa = 4"); }


    const int suits[4] = { Card::Kupe, Card::Spade, Card::Bastoni, Card::Dinari };

    for (int si = 0; si < 4; ++si) {
        int s = suits[si];
        bool hasA = false, has2 = false, has3 = false;

        for (size_t i = 0; i < hand_.size(); ++i) {
            if (hand_[i].suit() != s) continue;
            if (hand_[i].rank() == Card::As) hasA = true;
            if (hand_[i].rank() == Card::Dvica) has2 = true;
            if (hand_[i].rank() == Card::Trica) has3 = true;

        }

        if (hasA && has2 && has3) {
            acc += 3;
            outDescriptions.push_back(std::string("Napolitana (") + Card::suitToString(s) + ") = 3");
        }
    }

    return acc;
}
