#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <list>
#include <map>
#include <algorithm>

struct decoded_string {
    std::string output;
    std::string input;
    char key;
};
std::string decrypt_xor(std::string input, std::string key);
std::string encrypt_xor(std::string input, std::string key);
std::string encrypt_file_xor(std::string input, std::string key);
std::multimap<int, struct decoded_string> probe_keys(std::string input);
