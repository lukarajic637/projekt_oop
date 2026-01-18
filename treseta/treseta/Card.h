#ifndef CARD_H
#define CARD_H

#include <string>
#include <sstream>

class Card {
public:
    static const int Kupe = 0;
    static const int Spade = 1;
    static const int Bastoni = 2;
    static const int Dinari = 3;

    static const int As = 1;
    static const int Dvica = 2;
    static const int Trica = 3;
    static const int Cetrvorka = 4;
    static const int Petica = 5;
    static const int Sestica = 6;
    static const int Sedmica = 7;
    static const int Fanat = 8;
    static const int Konj = 9;
    static const int Kralj = 10;

    Card() : suit_(Kupe), rank_(Cetrvorka) {}
    Card(int suit, int rank) : suit_(suit), rank_(rank) {}

    int suit() const { return suit_; }
    int rank() const { return rank_; }

    std::string toString() const {
        std::ostringstream oss;
        oss << rankToString(rank_) << " od " << suitToString(suit_);
        return oss.str();
    }

    static std::string suitToString(int s) {
        switch (s) {
        case Kupe:    return "Kupe";
        case Spade:   return "Spade";
        case Bastoni: return "Bastoni";
        case Dinari:  return "Dinari";
        }
        return "?";
    }

    static std::string rankToString(int r) {
        switch (r) {
        case As:        return "As";
        case Dvica:     return "Dvica";
        case Trica:     return "Trica";
        case Cetrvorka: return "Cetvorka";
        case Petica:    return "Petica";
        case Sestica:   return "Sestica";
        case Sedmica:   return "Sedmica";
        case Fanat:     return "Fanat";
        case Konj:      return "Konj";
        case Kralj:     return "Kralj";
        }
        return "?";
    }

    static int roundStrength(int r) {
        switch (r) {
        case Trica:     return 10;
        case Dvica:     return 9;
        case As:        return 8;
        case Kralj:     return 7;
        case Konj:      return 6;
        case Fanat:     return 5;
        case Sedmica:   return 4;
        case Sestica:   return 3;
        case Petica:    return 2;
        case Cetrvorka: return 1;
        }
        return 0;
    }


    static int pointsInThirds(int r) {
        if (r == As) return 3;
        if (r == Dvica || r == Trica || r == Kralj || r == Konj || r == Fanat) return 1;
        return 0;
    }

private:
    int suit_;
    int rank_;
};

#endif
