#include "../includes/codec_xor.h"

template<typename A, typename B>
std::pair<B,A> flip_pair(const std::pair<A,B> &p)
{
    return std::pair<B,A>(p.second, p.first);
}

template<typename A, typename B>
std::multimap<B,A> flip_map(const std::map<A,B> &src)
{
    std::multimap<B,A> dst;
    std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), 
            flip_pair<A,B>);
    return dst;
}

int freqs_rank(std::string phrase)
{
    std::map<char, int> freqs;
    std::multimap<int, char> sorted;
    int score = 0, i = 0;
    std::string firsts {"ETAOIN SHRDLU"};
    std::string lasts {"VKJXQZ"};

    for(char c : phrase){
        if(freqs.count(c) > 0){
            freqs[c]++;
        }else{
            freqs[c] = 1;
        }
    }

    sorted = flip_map(freqs);

    i = 0;
    for(std::multimap<int, char>::iterator it = sorted.begin(); it != sorted.end(); it++){
        if (i >= 0)
            break;
        std::string character {it->second};
        if (lasts.find(character) != std::string::npos)
            score++;
        i++;
    }

    i = 0;
    for(std::multimap<int, char>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); it++){
        if (i == firsts.size())
            break;
        std::string character {it->second};
        if (firsts.find(character) != std::string::npos)
            score++;
        i++;
    }

    return score;
}

char dencrypt(int input, char key)
{
    int encoded = (input ^ key);

    return (char) encoded;
}

/*
 * Receives as input an hex encoded string and returns a decoded string
 */
std::string decrypt_xor(std::string input, std::string key)
{
    char single_key, coded;
    int size_key = key.size();
    std::string output;

    for(int i = 0; i < input.size(); i += 2){
        std::string character = input.substr(i, 2);
        int value = stoi(character, nullptr, 16);
        single_key = key[i % size_key];
        coded = dencrypt(value, single_key);
        output += toupper(coded);
    }

    return output;
}

/*
 * Receives as input a decoded string and returns an hex encoded string
 */
std::string encrypt_xor(std::string input, std::string key)
{
    char single_key, coded, character;
    char hex_coded[2];
    int size_key = key.size();
    std::string output;
    
    for(int i = 0; i < input.size(); i++){
        character = input[i];
        single_key = key[i % size_key];
        coded = dencrypt(character, single_key);
        sprintf(hex_coded, "%02X", coded);
        output += hex_coded;
    }

    return output;
}

/*
 * Receives as input an ifstream and returns the contents of the file encoded in hex
 */
std::string encrypt_file_xor(std::string filename, std::string key)
{
    // I don't know why but the ifstream iterator reads one more character when the
    // file has reached eof and it's really weird, somehow it corrupts the single_key
    // local variable, so that's why the last_hex_coded exists.
    char character, single_key, coded;;
    char hex_coded[2];
    int i = 0, size_key = key.size();
    std::string output, last_hex_coded {""};
    std::ifstream input {filename};

    while (input.good()){
        character = input.get();
        single_key = key[i % size_key];
        if (single_key == 'B')
            break;
        coded = dencrypt(character, single_key);
        sprintf(hex_coded, "%02X", coded);
        output += last_hex_coded;
        last_hex_coded = hex_coded;
        i++;
    }
    
    return output;
}

std::multimap<int, struct decoded_string> probe_keys(std::string input)
{
    std::multimap<int, struct decoded_string> ranking;
    std::string sdecoded, skey;
    int score;

    for(char key {'!'}; key <= '~'; key++){
        skey = key;
        sdecoded = decrypt_xor(input, skey);
        score = freqs_rank(sdecoded);
        struct decoded_string decoded {sdecoded, input, key};
        ranking.insert(std::pair<int, struct decoded_string>(score, decoded));
    }

    return ranking;
}
