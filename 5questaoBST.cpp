#include <iostream>
using namespace std;
/* 5ª Questão, 2º hackhaton, árvores binárias*/
int esq[100005], dir[100005];
int fila[100005];   //por essas fila que eu vou conseguir desenrolar para percorrer os níveis

int main() {
    int n, raiz;
    cin >> n >> raiz;
    for (int i = 1; i <= n; i++) cin >> esq[i] >> dir[i];

    if (n == 0 || raiz == 0) {
        cout << "-1 0" << endl;  
        return 0;
    }

    int inicio = 0, fim = 0;     
    fila[fim++] = raiz;

    int niveis = 0;
    int larguraMax = 0;

    while (inicio < fim) {
        int tamNivel = fim - inicio;          // aqui temos quantos nós há neste nível
        if (tamNivel > larguraMax) larguraMax = tamNivel;
        niveis++;

        // processa os nós do nível
        for (int k = 0; k < tamNivel; k++) {
            int v = fila[inicio++];          
            if (esq[v] != 0) fila[fim++] = esq[v];  
            if (dir[v] != 0) fila[fim++] = dir[v];
        }
    }

    cout << niveis - 1 << " " << larguraMax << endl;  
    return 0;
}