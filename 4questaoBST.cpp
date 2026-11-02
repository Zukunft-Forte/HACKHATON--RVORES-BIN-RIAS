#include <iostream>
using namespace std;
/* 4ª Questão, 2º hackhaton, árvores binárias*/
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

No* inserir(No* raiz, int c) {
    if (raiz == nullptr) return novoNo(c);
    No* atual = raiz;
    while (true) {
        if (c == atual->chave) return raiz;
        if (c < atual->chave) {
            if (atual->esq == nullptr) { atual->esq = novoNo(c); return raiz; }
            atual = atual->esq;
        } else {
            if (atual->dir == nullptr) { atual->dir = novoNo(c); return raiz; }
            atual = atual->dir;
        }
    }
}

// Nessa parte, montei a busca a profundidade da chave ou -1 se não existir, que nem prof alex solicitou
int profundidade(No* raiz, int c) {
    int prof = 0;
    No* atual = raiz;
    while (atual != nullptr) {
        if (c == atual->chave) return prof;
        if (c < atual->chave) atual = atual->esq;
        else atual = atual->dir;
        prof++;                 
    }
    return -1;                  // sai da árvore sem achar
}

int main() {
    int n, q;
    cin >> n;
    No* raiz = nullptr;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        raiz = inserir(raiz, x);
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        cout << profundidade(raiz, x) << "\n";
    }
    return 0;
}