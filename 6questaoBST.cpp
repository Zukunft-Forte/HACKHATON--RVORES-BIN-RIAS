#include <iostream>
using namespace std;
/* 6ª Questão 2º Hackhaton árvores binárias*/
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

// vendo o menor nó de uma subárvore, ou seja, na esquerda.
No* minimo(No* r) {
    while (r->esq != nullptr) r = r->esq;
    return r;
}

// Removendo a chave c e devolvendo a nova raiz da subárvore
No* remover(No* raiz, int c) {
    if (raiz == nullptr) return nullptr;       // se estivermos com achave ausente, nada muda
    if (c < raiz->chave) {
        raiz->esq = remover(raiz->esq, c);
    } else if (c > raiz->chave) {
        raiz->dir = remover(raiz->dir, c);
    } else {
        // achou o nó a remover
        if (raiz->esq == nullptr) {            // folha ou só filho direito
            No* filho = raiz->dir;
            delete raiz;
            return filho;
        }
        if (raiz->dir == nullptr) {            // só filho esquerdo
            No* filho = raiz->esq;
            delete raiz;
            return filho;
        }
        // dois filhos: utilizamos o sucessor em ordem, ou seja, menor da subárvore da direita
        No* suc = minimo(raiz->dir);
        raiz->chave = suc->chave;                    
        raiz->dir = remover(raiz->dir, suc->chave);  
    }
    return raiz;
}

void preOrdem(No* r, bool& primeiro) {
    if (r == nullptr) return;
    if (!primeiro) cout << " ";
    cout << r->chave;
    primeiro = false;
    preOrdem(r->esq, primeiro);
    preOrdem(r->dir, primeiro);
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
        raiz = remover(raiz, x);
    }
    bool primeiro = true;
    preOrdem(raiz, primeiro);
    cout << "\n";
    return 0;
}