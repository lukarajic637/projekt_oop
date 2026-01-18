#include "Game.h"
#include <iostream>
#include <exception>

int main() {
    try {
        Game g;
        g.run();
    }
    catch (const std::exception& ex) {
        std::cerr << "Greska: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}
