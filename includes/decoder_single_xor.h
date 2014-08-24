#include <string>
#include <iostream>
#include <list>
#include <map>
#include <algorithm>

struct decoded_string {
    std::string output;
    std::string input;
    char key;
};
std::string decrypt_sxor(std::string input, char key);
std::multimap<int, struct decoded_string> probe_keys(std::string input);
