#include <memory>
#include <bitset>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>

class Huffman {
public:
    std::unordered_map<std::string, std::string> encode(std::string data);   

private:
    struct Node {
        int freq;
        std::string chr;
        std::shared_ptr<Node> left, right;
    };
    std::shared_ptr<Node> generateTree(std::vector<std::shared_ptr<Node>> pq);
    void generateCodes(std::shared_ptr<Node> &node, std::string code, std::unordered_map<std::string, std::string> &m);
    void writeCompressedFile(std::shared_ptr<Huffman::Node> root, std::string data, std::unordered_map<std::string, std::string> codes);
    void writeStream(std::shared_ptr<Huffman::Node> root, std::vector<std::string> &vTree);
};

std::unordered_map<std::string, std::string> Huffman::encode(std::string data) {
    std::unordered_map<std::string, int> freq;
    for(auto &ch : data) {
        ++freq[std::string(1, ch)];
    }
    std::vector<std::shared_ptr<Huffman::Node>> pq;
    for(const auto &kv : freq) {
        std::string kvfirst(kv.first);
        pq.push_back(std::make_shared<Huffman::Node>(Huffman::Node{kv.second, kvfirst}));
    }
    auto root = generateTree(pq);
    std::unordered_map<std::string, std::string> codes;
    generateCodes(root, "", codes);
    /* flattenTree(root); */
    writeCompressedFile(root, data, codes);
    return codes;
}

void Huffman::generateCodes(std::shared_ptr<Huffman::Node> &node, std::string code, std::unordered_map<std::string, std::string> &m) {
    if(!node->left) {
        m[node->chr] = code;
        return;
    }
    generateCodes(node->right, code+"1", m);
    generateCodes(node->left, code+"0", m);
}

std::shared_ptr<Huffman::Node> Huffman::generateTree(std::vector<std::shared_ptr<Huffman::Node>> pq) {
    auto compare = [](const auto &a, const auto &b) { return a->freq > b->freq;};
    while(pq.size() > 1) {
        auto left = std::move(pq.back());
        pq.pop_back();
        auto right = std::move(pq.back());
        pq.pop_back();
        pq.push_back(std::make_shared<Huffman::Node>(Huffman::Node{left->freq+right->freq, left->chr+right->chr, left, right}));
        std::sort(pq.begin(), pq.end(), compare);
    }
    return std::move(pq.front());
}


/* void Huffman::traverseTree(std::shared_ptr<Huffman::Node> root) { */
/*     std::vector<std::string> flattree; */

/*     if(root == NULL || root->left == NULL || root->right == NULL) */
/*         return; */

/*     if(root->left != NULL) { */
/*         flattenTree(root->left); */

/*         auto tempRight = root->right; */
/*         root->right = root->left; */
/*         root->left = NULL; */

/*         auto t = root->right; */
/*         while(t->right != NULL) { */
/*             t = t->right; */
/*         } */
/*         t->right = tempRight; */
/*     } */
/*     flattenTree(root->right); */ 
/* } */

void Huffman::writeCompressedFile(std::shared_ptr<Huffman::Node> root, std::string data, std::unordered_map<std::string, std::string> codes) {
    std::string content;
    // write compressed data
    std::ofstream file("compressed.theus", std::ios::binary);
        
    for(auto &ch : data) {
        /* file.write((const char *)&asdf, asdf.size()); */
        file.write((const char *)&codes[std::string(1, ch)], codes.size());
    }

    // write binary tree to stream
    /* content += "!-!"; */
    std::vector<std::string> shit;
    writeStream(root, shit);
    /* content += "!-!"; */

    /* std::ofstream file("compressed.theus"); */
    /* std::string asdf = "hello"; */
    file.write((const char *)&NULL, 1);
    file.write((const char *)&shit, shit.size());
    file.close();
}
void Huffman::writeStream(std::shared_ptr<Huffman::Node> root, std::vector<std::string> &vTree) {
    if(root == NULL) return;

    for(auto &e : root->chr) {
        vTree.push_back(std::string(1, e));
    }
    
    writeStream(root->left, vTree);
    writeStream(root->right, vTree);
}

