#include <fstream>
#include "../includes/codec_xor.h"

int main(){
    std::string line;
    std::ifstream input {"4.txt"};
    std::multimap<int, struct decoded_string> partial_ranking, ranking;
    std::multimap<int, struct decoded_string>::reverse_iterator it;
    const int MAX_ENCODED_PER_INPUT {3};

    if (input.is_open()){
        while (std::getline(input,line)){
            partial_ranking = probe_keys(line);
            int i = 0;
            for(it = partial_ranking.rbegin(); it != partial_ranking.rend(); it++){
                ranking.insert(*it);
                i++;
                if (i == MAX_ENCODED_PER_INPUT)
                    break;
            }
        }
        for(it = ranking.rbegin(); it != ranking.rend(); it++){
            if (it->first >= 8){
                std::cout << it->second.key << "(" << it->first << ") " << it->second.output << std::endl;
            }
        }
        input.close();
    }else{
        std::cout << "Unable to open the file" << std::endl;
    }


    return 0;
}
