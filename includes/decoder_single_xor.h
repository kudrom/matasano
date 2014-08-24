#include <string>
#include <iostream>
#include <list>
#include <map>
#include <algorithm>

struct decoded_string {
    std::string output;
    int score;
    char key;
};
struct decoded_string decrypt_single_character_xor(std::string input);
