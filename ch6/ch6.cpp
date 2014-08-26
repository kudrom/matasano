#include "../includes/hamming.h"

int main(int argc, char *argv[])
{
    if (argc != 3){
        std::cout << "Usage: ch6 <str1> <str2>" << std::endl;
        return -1;
    }
    std::string str1 {argv[1]};
    std::string str2 {argv[2]};

    std::cout << hamming_distance(str1, str2) << std::endl;

    return 0;
}
