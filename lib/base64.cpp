#include "../includes/base64.h"
#include <cstdio>

std::map<int, char> build_map()
{
    std::map<int, char> mapping;
    char element = 'A';

    for (int i = 0; i < 64; i++){
        mapping[i] = element;
        if (element == 'Z'){
            element = 'a';
        }else if(element == 'z'){
            element = '0';
        }else if(element == '9'){
            element = '+';
        }else if(element == '+'){
            element = '/';
        }else{
            element++;
        }
    }

    return mapping;
}

std::map<char, int> build_reverse_map()
{
    std::map<char, int> mapping;
    char element = 'A';

    for (int i = 0; i < 64; i++){
        mapping[element] = i;
        if (element == 'Z'){
            element = 'a';
        }else if(element == 'z'){
            element = '0';
        }else if(element == '9'){
            element = '+';
        }else if(element == '+'){
            element = '/';
        }else{
            element++;
        }
    }

    return mapping;
}

/*
 * Get a hex encoded string as an input and returns a base64 encoded string
 */
std::string base64_encrypt_hex(std::string input)
{
    std::map<int, char> mapping;
    int hex, digit1, digit2;
    std::queue<int> output;
    std::string retval;

    mapping = build_map();

    for(int i = 0; i < input.size(); i += 3){
        std::string datum {input.substr(i, 3)};
        hex = stoi(datum, nullptr, 16);

        digit1 = hex % 64;
        hex >>= 6;
        digit2 = hex % 64;

        output.push(digit2);
        output.push(digit1);
    }

    while (!output.empty()){
        int element;
        element = output.front();
        retval += mapping[element];
        output.pop();
    }

    return retval;
}

/*
 * Get a string as an input and returns a plain string
 */
std::string base64_decrypt(std::string input)
{
    std::map<char, int> mapping;
    char byte1, byte2, byte3;
    int mapped;
    int32_t binary_datum {0};
    std::string retval;

    mapping = build_reverse_map();

    for(int i = 0; i < input.size(); i += 4){
        std::string datum {input.substr(i, 4)};

        binary_datum = 0;
        for(char c : datum){
            mapped = mapping[c];
            binary_datum |= mapped;
            binary_datum <<= 6;
        }
        binary_datum >>= 6;

        byte1 = (binary_datum % 256);
        binary_datum >>= 8;
        byte2 = (binary_datum % 256);
        binary_datum >>= 8;
        byte3 = (binary_datum % 256);

        retval += byte3;
        retval += byte2;
        retval += byte1;
    }

    return retval;
}
