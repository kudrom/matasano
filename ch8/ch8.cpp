#include <fstream>
using std::ifstream;
using std::getline;
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <map>
using std::multimap;
using std::pair;
#include <vector>
using std::vector;
#include <algorithm>
using std::find;

int repeated_strings(string ciphertext)
{
    int score {1};
    vector<string> readed;
    vector<string>::iterator it;
    int end {ciphertext.size()}, curr {0};

    while (curr < end){
        string chunk {ciphertext.substr(curr, 32)};
        it = find(readed.begin(), readed.end(), chunk);
        if (it != readed.end()){
            score++;
            cout << "found: " << chunk << endl;
        }else{
            readed.push_back(chunk);
        }
        curr += 32;
    }

    return score;
}

int main(int argc, char *argv[])
{
    if (argc != 2){
        cout << "Usage: ch8 <input_filename>" << endl;
        return -1;
    }
    string filename {argv[1]}, line;
    ifstream input {filename};
    multimap<int, string> ranking;

    int score;
    if (input.is_open()){
        while (getline(input, line)){
            score = repeated_strings(line);
            ranking.insert(pair<int, string>(score, line));
        }
    }

    int i {0};
    multimap<int, string>::reverse_iterator it;
    for(it = ranking.rbegin(); it != ranking.rend(); it++){
        cout << it->first << " : " << it->second << endl;
        if (i == 5){
            break;
        }
        i++;
    }

    return 0;
}
