// Eduardo Gwoszdz De Lazari e Micael Angelo Sabadin Presotto
// 22100612 e 22104063

#include <iostream>
#include <fstream>
#include "array_stack.h"
#include "array_queue.h"
#include <string>
using namespace std;

void limpar(string nome, int altura, int largura, int x, int y, string matriz_e) {
    string matriz_r = "";
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            matriz_r += "0";
        }   
    }
    structures::ArrayQueue<int> fila{static_cast<size_t>(altura*largura)};
    if (matriz_e[x * largura + y] == '1') {
        matriz_r[x * largura + y] = '1';
        fila.enqueue(x * largura + y);
    }
    while (!fila.empty()) {
        int coord = fila.dequeue();
        int c_x = coord / largura;
        int c_y = coord % largura;
        int c;
        
        if (c_x + 1 != altura) {
            c = coord + largura;
            if (matriz_e[c] == '1' && matriz_r[c] == '0') {
                matriz_r[c] = '1';
                fila.enqueue(c);
            }
        }

        if (c_x != 0) {
            c = coord - largura;
            if (matriz_e[c] == '1' && matriz_r[c] == '0') {
                matriz_r[c] = '1';
                fila.enqueue(c);
            }
        }

        if (c_y + 1 != largura) {
            c = coord + 1;
            if (matriz_e[c] == '1' && matriz_r[c] == '0') {
                matriz_r[c] = '1';
                fila.enqueue(c);
            }
        }

        if (c_y != 0) {
            c = coord - 1;
            if (matriz_e[c] == '1' && matriz_r[c] == '0') {
                matriz_r[c] = '1';
                fila.enqueue(c);
            }
        }
    }
    int k = 0;
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            if (matriz_r[i*largura + j] == '1') {
                k++;
            }
        }   
    }
    if (k == 1) k = 0;
    cout << nome + " " + to_string(k) << endl;
}

string getValorTag(string linha, string tag) {
    string comecoTag = "<" + tag + ">";
    string fimTag = "</" + tag + ">";
    size_t posicaoInicial = linha.find(comecoTag);
    size_t posicalFinal = linha.find(fimTag);

    if (posicaoInicial != string::npos && posicalFinal != string::npos) {
        posicaoInicial += comecoTag.length();
        return linha.substr(posicaoInicial, posicalFinal - posicaoInicial);
    }
    return "";
}

void getTags(string xml) {
    ifstream my_file(xml);
    string linha;
    structures::ArrayQueue<string> nome{101};
    structures::ArrayQueue<string> altura{101};
    structures::ArrayQueue<string> largura{101};
    structures::ArrayQueue<string> x{101};
    structures::ArrayQueue<string> y{101};
    structures::ArrayQueue<string> matriz{101};
    bool lerMatriz = false;
    string valorMatriz = "";
    while(getline(my_file, linha)) {
        string valorNome = getValorTag(linha, "nome");
        if (!valorNome.empty()) {
            nome.enqueue(valorNome);
        }

        string valorAltura = getValorTag(linha, "altura");
        if (!valorAltura.empty()) {
            altura.enqueue(valorAltura);
        }

        string valorLargura = getValorTag(linha, "largura");
        if (!valorLargura.empty()) {
            largura.enqueue(valorLargura);
        }

        string valorX = getValorTag(linha, "x");
        if (!valorX.empty()) {
            x.enqueue(valorX);
        }

        string valorY = getValorTag(linha, "y");
        if (!valorY.empty()) {
            y.enqueue(valorY);
        }
        
        if (linha.find("</matriz>") != string::npos) {
            lerMatriz = false;
            matriz.enqueue(valorMatriz);
            valorMatriz = "";
        } else if (linha.find("<matriz>") != string::npos) {
            lerMatriz = true;
        } else if (lerMatriz) {
            valorMatriz += linha;
        }
    }

    while (!nome.empty()) {
        limpar(nome.dequeue(), stoi(altura.dequeue()), stoi(largura.dequeue()), stoi(x.dequeue()), stoi(y.dequeue()), matriz.dequeue());
    }

    
}

bool verificaXml(string xml) {

    ifstream my_file(xml);
    if (my_file.is_open()){
        structures::ArrayStack<string> stack;
        string linha;
        while (getline(my_file, linha)){
            size_t inicio = linha.find('<');
            size_t final = linha.find('>', inicio);
            while (inicio != string::npos && final != string::npos){
                string tag = linha.substr(inicio + 1, final - inicio - 1);
                if (tag[0] == '/'){
                    string top = stack.top();
                    if(tag.substr(1) == top){
                        stack.pop();
                    }else{
                        return false;
                    }
                }else{
                    stack.push(tag);
                }
                inicio = linha.find('<', final);
                final = linha.find('>', inicio);
            }
        }
        my_file.close();
        if(stack.empty()){
            return true;
        }
        return false;
    } else{
        return false;
    }
}

int main() {

    char xmlfilename[100];

    cin >> xmlfilename;  // entrada
    
    if (!verificaXml(xmlfilename)) {
        printf("erro");
    } else {
        getTags(xmlfilename);
    }

    

    return 0;
}