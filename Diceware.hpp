#ifndef DICEWARE_HPP
#define DICEWARE_HPP

#include <string>
#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>

int loadDicewareWordlist(const std::string &fn, std::vector<std::string> &wordlist);
std::string dicewarePickRandomWord(const std::vector<std::string> &wl, std::string &str1, std::mt19937 &RNG);
std::string dicewarePickRandomWord(const std::vector<std::string> &wl, std::mt19937 &RNG);
std::string dicewareGeneratePassphrase(const std::vector<std::string> &wl, const int &numWords, std::mt19937 &RNG);
std::string dicewareGeneratePassphrase(const std::vector<std::string> &wl, const int &numWords, std::string &str1, std::mt19937 &RNG);
static int changeBase(const int &inp, const int &fromBase, const int &toBase);
static int toBase10(const int &inp, const int &fromBase);
static int fromBase10(const int &inp, const int &toBase);

struct BadListSize{ };

#endif