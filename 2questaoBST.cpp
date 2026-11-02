#include <iostream>
using namespace std;
/* 2ª Questão 2º hackhaton, árvores binárias*/
int esq[10005], dir[10005];
int pilha[10005];   
int ordem[10005];   

void imprimir(int v[], int tam) {
    for (int i = 0; i < tam; i++) {
        if (i > 0) cout << " ";
        cout << v[i];
    }
    cout << "\n";
}

int main() {
    int n, raiz;
    cin >> n >> raiz;
    for (int i = 1; i <= n; i++) cin >> esq[i] >> dir[i];

    // PRÉ-ORDEM: RAIZ, ESQUERDA E DIREITA
    int topo = 0, tam = 0;
    if (raiz != 0) pilha[topo++] = raiz;
    while (topo > 0) {
        int v = pilha[--topo];     // tira o topo
        ordem[tam++] = v;          // visita (raiz primeiro)
        if (dir[v] != 0) pilha[topo++] = dir[v]; // direita entra primeiro...
        if (esq[v] != 0) pilha[topo++] = esq[v]; // ...para a esquerda sair primeiro
    }
    imprimir(ordem, tam);

    // EM ORDEM: ESQUERDA, RAIZ, DIREITA
    topo = 0; tam = 0;
    int atual = raiz;
    while (atual != 0 || topo > 0) {
        while (atual != 0) {       // desce o máximo possível pela esquerda
            pilha[topo++] = atual;
            atual = esq[atual];
        }
        atual = pilha[--topo];     // volta ao último nó pendente
        ordem[tam++] = atual;      // visita
        atual = dir[atual];        // depois vai para a direita
    }
    imprimir(ordem, tam);

    // PÓS-ORDEM: ESQUERDA, DIREITA, RAIZ
    // Aqui, resolvi fazer "raiz, direita, esquerda", imprimindo de trás para frente para facilitar minha vida kk
    topo = 0; tam = 0;
    if (raiz != 0) pilha[topo++] = raiz;
    while (topo > 0) {
        int v = pilha[--topo];
        ordem[tam++] = v;
        if (esq[v] != 0) pilha[topo++] = esq[v]; // esquerda entra primeiro
        if (dir[v] != 0) pilha[topo++] = dir[v]; // direita sai primeiro
    }
    // Inverte: "raiz,direita,esquerda ao contrário vira "esquerda,direita,raiz"
    for (int i = 0; i < tam; i++) {
        if (i > 0) cout << " ";
        cout << ordem[tam - 1 - i];
    }
    cout << "\n";
    return 0;
}