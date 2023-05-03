#include <iostream>
#include <vector>
#include <fstream>
#include <memory>


struct Node {
    int freq;
    std::string chr;
    std::shared_ptr<Node> left, right;
};


int main() {

    FILE *file = fopen("compressed.bin", "rb");
    std::vector<Node> nodes;

    size_t size;
    fread(&size, sizeof(size_t), 1, file);


    nodes.resize(size);
    for(auto &node : nodes) {
        fread(&node, sizeof(node), 1, file);
    }
    fclose(file);

    for(auto &e : nodes) {
        std::cout<<e.chr<<std::endl;
    }


    return 0;
}
