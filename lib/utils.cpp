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

string pkcs7_pad_block(string input, int block_size)
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

string pkcs7_pad(string input, int block_size)
{
    size_t rest {input.size() % block_size};
    if (rest != 0){
        size_t size {input.size() - rest};
        string input_trimmed {input.substr(0, size)};
        string last_block {input.substr(size, block_size)};
        string last_block_padded {pkcs7_pad_block(last_block, block_size)};

        return input_trimmed + last_block_padded;
    }

    return input;
}

int repeated_strings(string ciphertext, int length)
{
    int score {0};
    vector<string> readed;
    vector<string>::iterator it;
    size_t end {ciphertext.size()}, curr {0};

    while (curr < end){
        string chunk {ciphertext.substr(curr, length)};
        it = find(readed.begin(), readed.end(), chunk);
        if (it != readed.end()){
            score++;
        }else{
            readed.push_back(chunk);
        }
        curr += length;
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

bool oracle_ecb(string input, int block_size)
{
    constexpr int MIN_BLOCK_SIZE {4};
    constexpr int MIN_SCORE {0};
    vector<string> blocks;
    int score {0};

#ifdef DEBUG
    printf("\n");
    for(unsigned char c : input){
        printf("%02X", c);
    }
    printf("\n");
#endif

    for(int start = 0; start < input.size(); start += block_size)
        blocks.push_back(input.substr(start, block_size));

    for(int i = 0; i < blocks.size(); i++){
        for(int ii = i+1; ii < blocks.size(); ii++){
            int equal_contiguous_bytes {0};

#ifdef DEBUG
            for(unsigned char c : blocks[i]){
                printf("%02X", c);
            }
            printf(" ^ ");
            for(unsigned char c : blocks[ii]){
                printf("%02X", c);
            }
            printf("\n");
#endif

            for(int x = 0; x < block_size; x++){
                int xored {blocks[i][x] ^ blocks[ii][x]};
                if (xored == 0){
                    equal_contiguous_bytes++;
                }else{
                    if (equal_contiguous_bytes > MIN_BLOCK_SIZE)
                        score++;
                    equal_contiguous_bytes = 0;
                }
            }

            // Detect overlapping keywords
            if (equal_contiguous_bytes > 0){
                if (equal_contiguous_bytes > MIN_BLOCK_SIZE){
                    score++;
                }else{
                    for(int x = 0; x < MIN_BLOCK_SIZE - 1; x++){
                        int xored {blocks[i+1][x] ^ blocks[ii+1][x]};
                        if (xored == 0){
                            equal_contiguous_bytes++;
                        }else{
                            break;
                        }
                        if (equal_contiguous_bytes > MIN_BLOCK_SIZE){
                            score++;
                            break;
                        }
                    }
                }
            }
        }
    }

#ifdef DEBUG
    cout << "SCORE: " << score << endl;
#endif

    return score > MIN_SCORE;
}
