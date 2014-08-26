#include "../includes/hamming.h"
#include "../includes/base64.h"
#include <cstdio>

int test_hamming_distance(int argc, char *argv[])
{
    if (argc != 3){
        std::cout << "Usage: ch6 <str1> <str2>" << std::endl;
        return -1;
    }
    std::string str1 {argv[1]};
    std::string str2 {argv[2]};

    std::cout << hamming_distance(str1, str2) << std::endl;

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2){
        std::cout << "Usage: ch6 <input_file>" << std::endl;
        return -1;
    }
    std::string input {argv[1]};
    std::string output;

    output = base64_decrypt(input);

    for (char c : output){
        printf("%02X", c);
    }
}
