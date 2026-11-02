#include <iostream>
using namespace std;
/* 3ª Questão, 2º hackhaton árvores binárias*/
struct No {
    int chave;
    No* esq;
    No* dir;
};

No* novoNo(int c) {
    No* p = new No;
    p->chave = c;
    p->esq = nullptr;
    p->dir = nullptr;
    return p;
}

// to inserindo c ligações por nós aqui, e o que for duplicado será descartado
No* inserir(No* raiz, int c) {
    if (raiz == nullptr) return novoNo(c);   // árvore vazia: o novo nó é a raiz
    No* atual = raiz;
    while (true) {
        if (c == atual->chave) return raiz;  // já existe, não insere
        if (c < atual->chave) {
            if (atual->esq == nullptr) {     // achou o lugar vazio à esquerda
                atual->esq = novoNo(c);
                return raiz;
            }
            atual = atual->esq;              // continua descendo
        } else {
            if (atual->dir == nullptr) {
                atual->dir = novoNo(c);
                return raiz;
            }
            atual = atual->dir;
        }
    }
}

// Percurso em ordem: esquerda, nó, direita, para ordem crescente 
void emOrdem(No* r, bool& primeiro) {
    if (r == nullptr) return;
    emOrdem(r->esq, primeiro);
    if (!primeiro) cout << " ";
    cout << r->chave;
    primeiro = false;
    emOrdem(r->dir, primeiro);
}

int main() {
    int n;
    cin >> n;
    No* raiz = nullptr;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        raiz = inserir(raiz, x);
    }
    bool primeiro = true;   // para ficar mais polido, organizei os espaços entre os números
    emOrdem(raiz, primeiro);
    cout << "\n";
    return 0;
}