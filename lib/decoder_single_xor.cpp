#include "../includes/decoder_single_xor.h"

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

std::string decrypt_sxor(std::string input, char key)
{
    std::list<char> buffer;
    std::string output;

    for(int i = 0; i < input.size(); i += 2){
        std::string character = input.substr(i, 2);
        int value = stoi(character, nullptr, 16);
        int encoded = (value ^ key);
        buffer.push_back((char) toupper(encoded));
    }
    for (char c : buffer){
        output += c;
    }

    return output;
}

std::multimap<int, struct decoded_string> probe_keys(std::string input)
{
    std::multimap<int, struct decoded_string> ranking;
    std::string sdecoded;
    int score;

    for(char key {'!'}; key <= '~'; key++){
        sdecoded = decrypt_sxor(input, key);
        score = freqs_rank(sdecoded);
        struct decoded_string decoded {sdecoded, input, key};
        ranking.insert(std::pair<int, struct decoded_string>(score, decoded));
    }

    return ranking;
}
