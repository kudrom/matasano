#include "../includes/base64.h"
#include <fstream>
#include <cryptopp/aes.h>
using CryptoPP::AES;

#include <cryptopp/filters.h>
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include <cryptopp/modes.h>
using CryptoPP::ECB_Mode;

int main(int argc, char *argv[])
{
    if (argc != 3){
        std::cout << "Usage: ch7 <input_file> <key>" << std::endl;
        return -1;
    }
    std::string filename {argv[1]};
    std::string key {argv[2]};
    std::string decoded, line, output;
    std::ifstream input {filename};

    decoded = filename;
    /*
    if (input.is_open()){
        while (std::getline(input, line)){
            decoded += base64_decrypt(line);
        }
    }
    */

    byte buffer_key[16];
    int i = 0;
    for (char c : key){
        buffer_key[i] = c;
        i++;
    }
    /*
    while (i < 16){
        buffer_key[i] = 0;
        i++;
    }
    */

    ECB_Mode<AES>::Encryption enc;
    enc.SetKey(buffer_key, 16);

    StringSource(decoded, true,
            new StreamTransformationFilter(enc,
                new StringSink(output)
            )
    );

    std::cout << output << std::endl;

    return 0;
}
