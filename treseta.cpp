#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

class Rules {
public:
    static string Suit(int s) {
        switch (s) {
        case 0: return "Bastona";
        case 1: return "Kupa";
        case 2: return "Dinara";
        case 3: return "Spadi";
        default: return "?";
        }
    }

    static string Rank(int r) {
        switch (r) {
        case 1: return "As";
        case 2: return "Dvica";
        case 3: return "Trica";
        case 8: return "Fanat";
        case 9: return "Konj";
        case 10: return "Kralj";
        default: return to_string(r);
        }
    }

    static int Strength(int r) {
        switch (r) {
        case 3:  return 10;
        case 2:  return 9;
        case 1:  return 8;
        case 10: return 7;
        case 9:  return 6;
        case 8:  return 5;
        case 7:  return 4;
        case 6:  return 3;
        case 5:  return 2;
        case 4:  return 1;
        default: return 0;
        }
    }

    static double Points(int r) {
        switch (r) {
        case 1:  return 1.0;
        case 2: return 1.0 / 3.0;
        case 3:  return 1.0 / 3.0;
        case 10: return 1.0 / 3.0;
        case 9:  return 1.0 / 3.0;
        case 8:  return 1.0 / 3.0;
        default: return 0.0;
        }
    }
};

class Card {
private:
    int s; 
    int r; 

public:
    Card(int suit = 0, int rank = 1) : s(suit), r(rank) {}

    int suit(){ return s; }
    int rank(){ return r; }

    string toString(){
        return Rules::Rank(r) + " " + Rules::Suit(s);
    }

    double pts(){ 
        return Rules::Points(r); 
    }
    int str(){ 
        return Rules::Strength(r); 
    }
};

class Deck {
private:
    vector<Card> cards;

public:
    void reset() {
        cards.clear();
        cards.reserve(40);

        for (int s = 0; s < 4; s++) {
            for (int r = 1; r <= 10; r++) {
                cards.push_back(Card(s, r));
            }
        }
    }

    void shuffles() {
        random_device rd;
        mt19937 gen(rd());
        shuffle(cards.begin(), cards.end(), gen);
    }

    Card draw() {
        Card c = cards.back();
        cards.pop_back();
        return c;
    }

    int size(){ 
        return cards.size();
    }
};


class Player {
private:
    string name;
    vector<Card> hand;

public:
    Player() : name("Igrac") {}

    string getName(){ 
        return name; 
    }

    void addToHand(Card c) { 
        hand.push_back(c); 
    }

    void sortHand() {
        sort(hand.begin(), hand.end(), [](Card& a, Card& b) {
            if (a.suit() != b.suit()) return a.suit() < b.suit();
            return a.rank() < b.rank();
            });
    }

    void printHand(){
        cout << name << " (ruka):\n";
        for (int i = 0; i < hand.size(); i++) {
            cout << "  " << i << " " << hand[i].toString() << "\n";
        }
    }

    vector<int> legalMoves(int leadSuit){
        vector<int> idx;

        if (leadSuit == -1) {
            for (int i = 0; i < (int)hand.size(); i++) {
                idx.push_back(i);
            }
            return idx;
        }

        bool hasSuit = false;
        for (auto& c : hand) {
            if (c.suit() == leadSuit) {
                hasSuit = true; 
                break; 
            }
        }

        for (int i = 0; i < (int)hand.size(); i++) {
            if (!hasSuit || hand[i].suit() == leadSuit) {
                idx.push_back(i);
            }
        }

        return idx;
    }

    int Bot_c(int leadSuit){
        auto legal = legalMoves(leadSuit);
        return legal.front();
    }

    int Player_c(int leadSuit){
        auto legal = legalMoves(leadSuit);
        while (true) {
            cout << "Odaberi kartu (index). Legalne: ";
            for (int i : legal) {
                cout << i << " ";
            }
            cout << "\n> ";
            int pick;
            cin >> pick;
            for (int i : legal) {
                if (i == pick) {
                    return pick;
                }
            }
            cout << "Neispravno.\n";
        }
    }

    Card play(int idx) {
        Card c = hand[idx];
        hand.erase(hand.begin() + idx);
        return c;
    }
};


int main() {
    Deck d;
    d.reset();
    d.shuffles();

    Player p;

    for (int i = 0; i < 10; i++) {
        p.addToHand(d.draw());
    }

    p.sortHand();
    p.printHand();

    int leadSuit = 0;
    auto legal = p.legalMoves(leadSuit);

    cout << "\nLegalne karte ako su " << Rules::Suit(leadSuit) << " prvi odigrani: ";
    for (int idx : legal) {
        cout << idx << " ";
    }
    cout << "\n";

    return 0;
}

