#include <iostream>
#include <string>
#include "huffman.h"

int main() {
    Huffman hf;

    std::string data("hello");
    std::unordered_map<std::string, std::string> codes = hf.encode(data);   

    /* for(auto &ch : data) { */
    /*     std::cout<<codes[std::string(1, ch)]<<std::endl; */
    /* } */

    return 0;
}
