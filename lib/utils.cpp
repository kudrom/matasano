#include "../includes/utils.h"

int hamming_distance(string str1, string str2)
{
    int size = min(str1.size(), str2.size());
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

string pkcs7_pad(string input, int block_size)
{
    int left;
    left = block_size - input.size();
    string output {input};

    if (left > 0){
        for (int i = 0; i < left; i++){
            output += left;
        }
    }

    return output;
}

int repeated_strings(string ciphertext, int length)
{
    int score {0};
    vector<string> readed;
    vector<string>::iterator it;
    int end {ciphertext.size()}, curr {0};

    while (curr < end){
        string chunk {ciphertext.substr(curr, length)};
        it = find(readed.begin(), readed.end(), chunk);
        if (it != readed.end()){
            score++;
        }else{
            readed.push_back(chunk);
        }
        curr += 32;
    }

    return score;
}

string gen_random_string(int len)
{
    string alphanum {"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    string output;

    for (int i = 0; i < len; i++){
        output += alphanum[rand() % (alphanum.size() -1 )];
    }

    return output;
}
