#include "../includes/base64.h"

std::map<int, std::string> build_map()
{
    std::map<int, std::string> mapping;
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

std::string base64_encrypt_hex(std::string input)
{
    std::map<int, std::string> mapping;
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

std::string base64_decrypt(std::string input)
{
    std::map<int, std::string> mapping;
    int hex, digit1, digit2;
    std::queue<int> output;
    std::string retval;

    mapping = build_map();
}
