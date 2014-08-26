#include "../includes/hamming.h"

int hamming_distance(std::string str1, std::string str2)
{
    int size = std::min(str1.size(), str2.size());
    int score = 0, xored;

    for (int i = 0; i < size; i++){
        char ch1 = str1[i];
        char ch2 = str2[i];
        xored = (ch1 ^ ch2);
        while (xored > 0){
            if ((xored & 1) == 1){
                score++;
            }
            xored >>= 1;
        }
    }

    return score;
}
