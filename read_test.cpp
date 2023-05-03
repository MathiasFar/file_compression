#include <iostream>
#include <fstream>

int main() {


    std::ifstream file ("test.7z", std::ios::binary);

    std::string s;

    file.read((char *)&s, 500);
    file.close();

    std::cout<<s<<std::endl;

    return 0;
}
