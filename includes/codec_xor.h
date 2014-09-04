#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cassert>
#include <list>
#include <map>
#include <algorithm>
#include "padding.h"

struct decoded_string {
    std::string output;
    std::string input;
    char key;
};
std::string decrypt_xor(std::string input, std::string key);
std::string encrypt_xor(std::string input, std::string key);
std::string encrypt_file_xor(std::string input, std::string key);
std::multimap<int, struct decoded_string> probe_keys(std::string input);

std::string decrypt_xor_cbc(std::string input, std::string key, std::string iv);
