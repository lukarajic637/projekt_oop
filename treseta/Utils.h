#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <iostream>
#include <string>

#ifdef _WIN32
inline void clearConsole() { std::system("cls"); }
#else
inline void clearConsole() { std::system("clear"); }
#endif

inline void pauseAndClear() {
    std::cout << "\n(Enter za nastavak)";
    std::string tmp;
    std::getline(std::cin, tmp);
    clearConsole();
}

#endif
