#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <map>

using namespace std;

int main()
{
    string input {"49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"};
    queue<int> output;
    map<int, string> mapping;
    int digit, binary;

    char element = 'A';
    for (int i = 0; i < 64; i++){
        mapping[i] = element;
        if (element == 'Z'){
            element = 'a';
        }else if(element == 'z'){
            element = '0';
        }else if(element == '9'){
            element = '+';
        }else if(element == '+'){
            element = '/';
        }else{
            element++;
        }
    }

    for(int i = 0; i < input.size(); i += 3){
        stack<int> aux;
        string datum {input.substr(i, 3)};
        binary = stoi(datum, nullptr, 16);
        while (binary > 0){
            digit = binary % 64;
            aux.push(digit);
            binary >>= 6;
        }
        while (!aux.empty()){
            output.push(aux.top());
            aux.pop();
        }
    }

    while (!output.empty()){
        int element;
        element = output.front();
        cout << mapping[element];
        output.pop();
    }
}
