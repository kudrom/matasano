#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <algorithm>
using std::find;
using std::min;

int hamming_distance(string str1, string str2);

string pkcs7_pad(string input, int block_size);

int repeated_strings(string ciphertext);
