#include  "../includes/padding.h"

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
