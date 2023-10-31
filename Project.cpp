#include<bits/stdc++.h>
using namespace std;

class Node{
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

class Project{
    private:
    Node* creatingTree(unordered_map<char, int> m, int N);
    void printing(Node* root, unordered_map<char, string> &ans, string s);

    public:
    Node *root = NULL;
    vector<char> randVec;
    unordered_map<char, string> huffmanEncoding(unordered_map<char, int> m, int N);
    string decodeHuffmanData(Node* root, string binaryString);
    string encryption(string s);
    string decryption(string s);
};

Node* Project::creatingTree(unordered_map<char, int> m, int N) {
    priority_queue<Node*, vector<Node*>, compare> pq;
    Node *t, *p, *q;
    t = p = q = nullptr;

    for(auto it=m.begin(); it!=m.end(); it++){
        t = new Node(it->first, it->second);
        pq.push(t);
    }

    while (pq.size() > 1) {
        p = pq.top();
        pq.pop();
        q = pq.top();
        pq.pop();
        int freq = p->freq + q->freq;
        t = new Node('\0', freq);
        t->left = p;
        t->right = q;
        pq.push(t);
    }

    return pq.top();
}

void Project::printing(Node* root, unordered_map<char, string> &ans, string s) {
    if (root->left == nullptr && root->right == nullptr) {
        ans[root->ch] = s;
        return;
    }

    if (root->left) {
        printing(root->left, ans, s + '0');
    }
    if (root->right) {
        printing(root->right, ans, s + '1');
    }
}

unordered_map<char, string> Project::huffmanEncoding(unordered_map<char, int> m, int N){
    root = creatingTree(m, N);
    unordered_map<char, string> ans;
    string s = "";
    printing(root, ans, s);
    return ans;
}

string Project::decodeHuffmanData(Node* root, string binaryString){
    string res;
    Node *temp = root;
    for(int i=0; i<binaryString.length(); i++){
        if(binaryString[i] == '0') temp = temp->left;
        else temp = temp->right;
                
        if(temp->left == NULL && temp->right == NULL){
            res += temp->ch;
            temp = root;
        }
    }
    return res;
}

string Project::encryption(string s){
    for(int i=0; s[i] != '\0'; i++){
        int randNum = rand()%5;
        randVec.push_back(randNum);
        s[i] += randNum;
    }
    return s;
}

string Project::decryption(string s){
    for(int i=0; s[i] != '\0'; i++){
        s[i] -= randVec[i];
    }
    return s;
}

int main(){
    string s; 
    cin>>s;
    unordered_map<char, int> m;
    for(int i=0; s[i] != '\0'; i++){
        m[s[i]]++;
    }

    Project p1;
    unordered_map<char, string> ans = p1.huffmanEncoding(m, m.size());
    for(auto it = ans.begin(); it != ans.end(); it++){
        cout<<it->first<<": "<<it->second<<endl;
    }

    string cs = "";
    for(int i=0; i<s.length(); i++){
        cs += ans[s[i]];
    }
    cout<<cs<<endl;

    string res = p1.decodeHuffmanData(p1.root, cs);
    cout<<res<<endl;

    //Encryption and decryption
    string es = p1.encryption(s);
    cout<<"Encrypted String: "<<es<<endl;
    string ds = p1.decryption(es);
    cout<<"Decrypted String: "<<ds<<endl;

    return 0;
}