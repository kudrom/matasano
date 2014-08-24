#include <fstream>
#include "../includes/decoder_single_xor.h"

int main(){
    std::string line;
    std::ifstream input {"4.txt"};
    struct decoded_string output;

    if (input.is_open()){
        while (std::getline(input,line)){
            output = decrypt_single_character_xor(line);
            std::cout << output.score << " " << output.output << std::endl;
        }
        input.close();
    }else{
        std::cout << "Unable to open the file" << std::endl;
    }

    return 0;
}
