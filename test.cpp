#include <iostream>
#include <sstream>
#include <string>
#include "linecipher.h"
int main() {
    linecipher::init();
    std::string input = "hello! my name is josh! nice to meet you!";
    std::string encoded = linecipher::encode(input);
    std::cout << encoded << std::endl;
    std::istringstream iss(encoded);
    std::string t, m, b;
    std::getline(iss, t);
    std::getline(iss, m);
    std::getline(iss, b);
    std::string decoded = linecipher::decode(t, m, b);
    std::cout << decoded << std::endl;
    return 0;
}
