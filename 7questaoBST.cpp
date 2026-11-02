#include <iostream>
using namespace std;
/* 7ª Questão 2º hackhaton, árvovres binárias*/
int esq[100005], dir[100005];
int alt[100005];       
int pilha[100005];
int ordem[100005];

int main() {
    int n, raiz;
    cin >> n >> raiz;
    for (int i = 1; i <= n; i++) cin >> esq[i] >> dir[i];

    // Aqui estou desenrolando para implementar a ordem Raiz, Direita, esquerda .
    // Ela é lida de trás para frente, com todo filho necessitando de aparecer antes de seu pai.
    int topo = 0, tam = 0;
    if (raiz != 0) pilha[topo++] = raiz;
    while (topo > 0) {
        int v = pilha[--topo];
        ordem[tam++] = v;
        if (esq[v] != 0) pilha[topo++] = esq[v];
        if (dir[v] != 0) pilha[topo++] = dir[v];
    }

    int maiorDesequilibrio = 0;
    alt[0] = 0;                              // subárvore vazia tem altura 0
    for (int i = tam - 1; i >= 0; i--) {     
        int v = ordem[i];
        int he = alt[esq[v]];               
        int hd = alt[dir[v]];              
        int dif = he - hd;
        if (dif < 0) dif = -dif;            
        if (dif > maiorDesequilibrio) maiorDesequilibrio = dif;
        alt[v] = 1 + (he > hd ? he : hd);   
    }

    if (maiorDesequilibrio <= 1) cout << "SIM\n";
    else cout << "NÃO\n";
    cout << maiorDesequilibrio << "\n";
    return 0;
}