#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;
#include <cstdio>
#include "../includes/utils.h"

int main(int argc, char *argv[])
{
    if (argc != 3){
        cout << "Usage: ch9 <input> <block_size>" << endl;
        return -1;
    }
    string input {argv[1]};
    int block_size {atoi(argv[2])};
    string padded {pkcs7_pad_block(input, block_size)};

    for (char c : padded){
        printf("%02X", c);
    }

    return 0;
}
