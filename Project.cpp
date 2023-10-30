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
    Node* creatingTree(string S, vector<int> f, int N) {
        priority_queue<Node*, vector<Node*>, compare> pq;
        Node *t, *p, *q;
        t = p = q = nullptr;
        for (int i = 0; i < N; i++) {
            t = new Node(S[i], f[i]);
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

    void printing(Node* root, string &ans, string s) {
        if (root->left == nullptr && root->right == nullptr) {
            ans += s;
            return;
        }

        if (root->left) {
            printing(root->left, ans, s + '0');
        }
        if (root->right) {
            printing(root->right, ans, s + '1');
        }
    }
    public:
        Node *root = NULL;
        string huffmanEncoding(string S, vector<int> f, int N){
            root = creatingTree(S, f, N);
            string ans;
            string s = "";
            printing(root, ans, s);
            return ans;
        }

        string decodeHuffmanData(Node* root, string binaryString){
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


};

int main(){
    Project p1;
    string ans = p1.huffmanEncoding("abcdef", {5, 9, 12, 13, 16, 45}, 6);
    cout<<ans<<endl;
    string st = p1.decodeHuffmanData(p1.root, ans);
    cout<<st<<endl;
    return 0;
}