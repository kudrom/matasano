#include "../includes/codec_xor.h"

int main(int argc, char *argv[])
{
    if (argc != 3){
        std::cout << "Usage ch5 <input_filename> <key>" << std::endl;
        return 0;
    }

    std::string input_filename {argv[1]};
    std::string key {argv[2]};
    std::string output;

    output = encrypt_file_xor(input_filename, key);
    std::cout << output << std::endl;
}
