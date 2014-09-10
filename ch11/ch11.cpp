#include "../includes/utils.h"
#include <cstdlib>
#include <fstream>
using std::ifstream;

#include <cryptopp/aes.h>
using CryptoPP::AES;

#include <cryptopp/filters.h>
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include <cryptopp/modes.h>
using CryptoPP::ECB_Mode;
using CryptoPP::CBC_Mode;
using CryptoPP::CipherModeDocumentation;

int main(int argc, char *argv[])
{
    if (argc != 3){
        cout << "Usage: ch11 <# rounds> <input_filename>" << endl;
        return -1;
    }
    int rounds;
    sscanf(argv[1], "%d", &rounds);
    ifstream file {argv[2]};
    string raw_input, output, line;
    byte iv[16];

    for(int i = 0; i < 16; i++){
        iv[i] = '\0';
    }

    if (file.is_open()){
        while(getline(file, line)){
            raw_input += line;
        }
    }

    while (rounds > 0){
        string key = gen_random_string(16);
        byte buffer_key[16];
        int i = 0;
        for (char c : key){
            buffer_key[i] = c;
            i++;
        }

        int len_start {rand() % 5};
        int len_end {rand() % 5};
        len_start += 5;
        len_end += 5;
        string input {raw_input};
        input = gen_random_string(len_start) + input + gen_random_string(len_end);
        input = pkcs7_pad(input, 16);

        int ecb_or_cbc {rand() % 2};
        if (ecb_or_cbc == 0){
            cout << "ECB ";
            ECB_Mode<AES>::Encryption enc;
            enc.SetKey(buffer_key, 16);

            StringSource ss (input, true,
                    new StreamTransformationFilter(enc,
                        new StringSink(output)
                    )
            );
        }else{
            cout << "CBC ";
            CBC_Mode<AES>::Encryption enc;
            enc.SetKeyWithIV(buffer_key, 16, iv);

            StringSource ss (input, true,
                    new StreamTransformationFilter(enc,
                        new StringSink(output)
                    )
            );
        }

        int score = repeated_strings(output, 16);
        if (score > 2){
            cout << "This is in ECB" << endl;
        }else{
            cout << "This is in CBC" << endl;
        }

        rounds--;
    }

    return 0;
}
