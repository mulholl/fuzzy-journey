#ifndef FUZZY_JOURNEY_FUNCTIONS_HPP
#define FUZZY_JOURNEY_FUNCTIONS_HPP

#include <sstream>
#include <string>
#include <iomanip>
#include <openssl/sha.h> // For obtaining the SHA-256 checksum of the wordlist
#include <fstream>
#include <cstdio>
#include <iostream>
#include <cstdlib>

std::string sha256(const std::string &str);
std::string sha256_file(const std::string &fn);
bool file_sha256_check(const std::string &fn, const std::string &str);
bool file_sha256_check(const std::string &fn, const std::string &str, std::string &ret);

#endif