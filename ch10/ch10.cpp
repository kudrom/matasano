#include "../includes/codec_xor.h"
#include "../includes/base64.h"
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::getline;

int main(int argc, char *argv[])
{
    if (argc != 3){
        cout << "Usage: ch10 <input_filename> <key>" << endl;
        return -1;
    }
    string input, output, line, iv;
    string filename {argv[1]};
    string key {argv[2]};
    ifstream input_file {filename};

    if(input_file.is_open()){
        while(getline(input_file, line)){
            input += base64_decrypt(line);
        }

        for(int i = 0; i < key.size(); i++){
            iv += '\0';
        }

        output = decrypt_xor_cbc(input, key, iv);
    }

    cout << output << endl;

    return 0;
}
