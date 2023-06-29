#include <string>

class NoTrie {
    public:
        NoTrie() {
            for (int i = 0; i < 26; i++) filhos[i] = nullptr;
            posicao = 0;
            comprimento = 0;
            prefixos = 0;
        }

        NoTrie(unsigned long posicao_) : NoTrie() {posicao = posicao_;}

        NoTrie(unsigned long posicao_, unsigned long comprimento_) : NoTrie(posicao_) {comprimento = comprimento_;}

        void deletar() {
            for (int i = 0; i < 26; i++) {
                if (filhos[i]) filhos[i]->deletar();
                delete filhos[i];
            }
        }

        NoTrie *filhos[26];
        unsigned long posicao;
        unsigned long comprimento;
        int prefixos;
};

class Trie {
    public:
        Trie() {
            raiz = new NoTrie();
        }

        ~Trie() {
            raiz->deletar();
            delete raiz;
        }

        void inserir(std::string palavra, unsigned long posicao_, unsigned long comprimento_) {
            NoTrie* atual = raiz;
            for (char letra : palavra)
                letra = tolower(letra);
            for (std::size_t i = 0; i < palavra.length(); i++) {
                int pos = palavra[i]-'a';
                if (!atual->filhos[pos]) atual->filhos[pos] = new NoTrie(palavra[i]);
                if (i == palavra.length() - 1) {
                    atual->filhos[pos]->comprimento = comprimento_;
                    atual->filhos[pos]->posicao = posicao_;
                }
                atual->prefixos++;
                atual = atual->filhos[pos];
            }
            
        }

        NoTrie* procurar(std::string palavra) {
            NoTrie* atual = raiz;
            for (char letra : palavra)
                letra = tolower(letra);
            for (std::size_t i = 0; i < palavra.length(); i++) {
                if (!atual->filhos[palavra[i]-'a']) return nullptr;
                atual = atual->filhos[palavra[i]-'a'];
            }
            int prefixos_ = atual->prefixos;
            if (atual->comprimento) prefixos_++;
            atual->prefixos = prefixos_;
            return atual;
        }

        NoTrie *raiz;
};