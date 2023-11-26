#include "Project.h"
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    Project p1;

    //Taking input
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cout << "Unable to open file." << endl;
        return 1;
    }
    string s;
    string line;
    while (getline(inputFile, line)) {
        s += line + "\n";
    }
    if(s == ""){
        cout<<"Nothing in input file"<<endl;
        return 0;
    }
    inputFile.close();

    unordered_map<char, int> m;
    string es = "";
    string cs = "";
    string ds = "";
    string res = "";
    unordered_map<char, string> ans;

    ofstream encryptedFile;
    ofstream decryptedFile;
    ofstream encodedFile;
    ofstream decodedFile;

    //Switch case
    int cont = true;
    int opt;
    while (cont == true)
    {
        cout<<"Choose one option:-"<<endl;
        cout<<"1. Encryption\n2. Decryption\n3. Encoding\n4. Decoding"<<endl;
        cin>>opt;
        switch (opt){
        case 1:
            //Encrypt File
            encryptedFile.open("encrypted.txt");
            es = p1.encryption(s);
            encryptedFile<<es;
            encryptedFile.close();
            break;

        case 2:
            //Decrypt File
            if(es.empty()) cout<<"Want Encrypted File"<<endl;
            else{
                decryptedFile.open("decrypted.txt");
                ds = p1.decryption(es);
                decryptedFile<<ds;
                decryptedFile.close();
            }
            break;

        case 3:
            //Encoded File
            for (int i = 0; s[i] != '\0'; i++) {
                m[s[i]]++;
            }
            ans = p1.huffmanEncoding(m, m.size());
            /* for (auto it = ans.begin(); it != ans.end(); it++) {
                cout << it->first << ": " << it->second << endl;
            } */
            for (int i = 0; i < s.length(); i++) {
                cs += ans[s[i]];
            }
            encodedFile.open("encoded.txt");
            encodedFile << cs;
            encodedFile.close();
            break;
        
        case 4:
            //Decoded File
            if(cs.empty()) cout<<"Want Encoded File"<<endl;
            else{
                res = p1.decodeHuffmanData(p1.root, cs);
                decodedFile.open("decoded.txt");
                decodedFile<<res;
                decodedFile.close();
            }
            break;
        
        default:
            cout<<"No such option is available."<<endl;
            break;
        }
        cout<<"You want to continue? 1 for true and 0 for false: ";
        cin>>cont;
    }

    return 0;
}
