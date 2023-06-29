#include <iostream>
#include <fstream>
#include "trie.h"

int main() {
    
    using namespace std;

    string filename;
    string word;

    cin >> filename;
    Trie *t = new Trie();
    
    ifstream my_file(filename);
    if (my_file.is_open()) {
        string linha;
        size_t tamanho_anterior = 0;
        while (getline(my_file, linha)) {
            string palavra = linha.substr(linha.find('[',0) + 1, linha.find(']',0) - 1);
            t->inserir(palavra, tamanho_anterior, linha.length());
            tamanho_anterior += linha.length() + 1;
        }
        my_file.close();
    }

    while (1) {
        cin >> word;
        if (word.compare("0") == 0) {
            break;
        }
        NoTrie* n = t->procurar(word);
        if (n) {
            cout << word << " is prefix of " << n->prefixos << " words" << endl;
            if (n->comprimento) {
                cout << word << " is at (" << n->posicao << "," << n->comprimento << ")" << endl;
            }
        } else {
            cout << word << " is not prefix" << endl;
        }
    }

    return 0;
}
