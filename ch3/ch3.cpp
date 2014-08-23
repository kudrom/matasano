#include <string>
#include <iostream>
#include <list>
#include <map>
#include <algorithm>

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

int freqs_rank(std::list<char> phrase)
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
        if (i == 6)
            break;
        std::string character {it->second};
        if (lasts.find(character) != std::string::npos)
            score++;
        i++;
    }

    i = 0;
    for(std::multimap<int, char>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); it++){
        if (i == 13)
            break;
        std::string character {it->second};
        if (firsts.find(character) != std::string::npos)
            score++;
        i++;
    }

    return score;
}

int main()
{
    std::string input {"1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"};
    std::list<char> output, actual;
    int maximum, ranking;
    char best_key;

    for(char key {'A'}; key <= 'Z'; key++){
        actual.clear();
        for(int i = 0; i < input.size(); i += 2){
            std::string character = input.substr(i, 2);
            int value = stoi(character, nullptr, 16);
            int encoded = (value ^ key);
            actual.push_back((char) toupper(encoded));
        }
        ranking = freqs_rank(actual);
        if (ranking >= maximum){
            output = actual;
            best_key = key;
            maximum = ranking;
        }
    }

    std::cout << "key: " << best_key << "(" << maximum << ")" << " => ";
    for(char c : output){
        std::cout << c;
    }
    std::cout << std::endl;
}
