#include "../includes/hamming.h"
#include "../includes/base64.h"
#include "../includes/codec_xor.h"
#include <cstdio>
#include <fstream>
#include <cassert>
#include <cmath>

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
    std::string filename {argv[1]};
    std::string decoded, line;
    std::ifstream input {filename};
    int KEYSIZE {40};
    std::multimap<double, int> keysize_mapping;

    if (input.is_open()){
        while (std::getline(input, line)){
            decoded += base64_decrypt(line);
        }
    }

    for (int i = 2; i < KEYSIZE; i++){
        std::string str1 {decoded.substr(0, i)};
        std::string str2 {decoded.substr(i, i)};
        assert(str1.size() == str2.size());

        int distance {hamming_distance(str1, str2)};
        double score = (distance / (double) i);
        keysize_mapping.insert(std::pair<double, int>(score, i));
    }
    std::multimap<double, int>::iterator it {keysize_mapping.begin()};
    std::vector<int> better_keysizes;
    for (int i = 0; it != keysize_mapping.end(); it++, i++){
        if (i == 8){
            break;
        }
        better_keysizes.push_back(it->second);
    }

    for(int keysize : better_keysizes){
        int blocks = ceil(decoded.size() / keysize);
        std::vector<std::string> transposed;
        printf("keysize: %d\n", keysize);
        for(int i = 0; i < keysize; i++){
            transposed.push_back(std::string {});
            for(int block = 0; block < blocks; block++){
                int index = (block * keysize) + i;
                if (index < decoded.size()){
                    char hex[2];
                    sprintf(hex, "%02X", decoded[index]);
                    transposed[i] += hex;
                }else{
                    transposed[i] += '\0';
                }
            }
        }
        for(std::string str : transposed){
            std::multimap<int, struct decoded_string> ranking = probe_keys(str);
            std::multimap<int, struct decoded_string>::reverse_iterator rit;
            int limit = 0;
            for(rit = ranking.rbegin(); rit != ranking.rend(); rit++, limit++){
                char key = rit->second.key;
                std::cout << key << " ";
                if (limit == 2)
                    break;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
