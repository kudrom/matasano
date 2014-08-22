#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3){
        cout << "Usage:" << "ch2 <input1> <input2>" << endl;
        return -1;
    }

    string input1 {argv[1]};
    string input2 {argv[2]};

    for (int i = 0; i < input1.size(); i++){
        int x = stoi(input1.substr(i, 1), nullptr, 16);
        int y = stoi(input2.substr(i, 1), nullptr, 16);
        cout << (x ^ y);
    }

    return 0;
}
