#ifndef PROJECT_H
#define PROJECT_H

#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

class Node {
public:
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(int freq) : ch('\0'), freq(freq), left(nullptr), right(nullptr) {}

    Node(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}

    ~Node() {
        delete left;
        delete right;
    }
};

struct compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

class Project {
private:
    Node* creatingTree(unordered_map<char, int> m, int N);
    void printing(Node* root, unordered_map<char, string>& ans, string s);

public:
    Node* root = nullptr;
    vector<int> randVec;

    unordered_map<char, std::string> huffmanEncoding(unordered_map<char, int> m, int N);
    string decodeHuffmanData(Node* root, string binaryString);
    string encryption(string s);
    string decryption(string s);
};

#endif