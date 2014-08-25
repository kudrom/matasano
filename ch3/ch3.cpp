#include "../includes/codec_xor.h"

int main()
{
    std::string input {"1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"};
    std::multimap<int, struct decoded_string> ranking;

    ranking = probe_keys(input);

    std::multimap<int, struct decoded_string>::reverse_iterator rit;
    for(rit = ranking.rbegin(); rit != ranking.rend(); rit++){
        std::cout << rit->second.key << "(" << rit->first << ") " << rit->second.output << std::endl;
    }

    return 0;
}
