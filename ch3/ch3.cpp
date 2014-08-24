#include "../includes/decoder_single_xor.h"

int main()
{
    std::string input {"1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"};
    struct decoded_string output;

    output = decrypt_single_character_xor(input);

    std::cout << "key: " << output.key << "(" << output.score << ") " << output.output << std::endl;

    return 0;
}
