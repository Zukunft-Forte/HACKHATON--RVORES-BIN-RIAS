#include <iostream>
using namespace std;
/* 12ª Questão 2º hackhaton árvores binárias*/
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

int chaves[3005];   // chaves em ordem crescente
int qtd = 0;

// Guarda as chaves da BST em ordem crescente no vetor
void extrair(No* r) {
    if (r == nullptr) return;
    extrair(r->esq);
    chaves[qtd++] = r->chave;
    extrair(r->dir);
}

// Constrói árvore balanceada com chaves[l..r], raiz no índice (l+r)/2
No* construir(int l, int r) {
    if (l > r) return nullptr;
    int m = (l + r) / 2;          // divisão inteira
    No* no = novoNo(chaves[m]);
    no->esq = construir(l, m - 1);
    no->dir = construir(m + 1, r);
    return no;
}

// Altura em arestas: árvore vazia = -1, um só nó = 0
int altura(No* r) {
    if (r == nullptr) return -1;
    int he = altura(r->esq);
    int hd = altura(r->dir);
    return 1 + (he > hd ? he : hd);
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
    int n;
    cin >> n;
    No* original = nullptr;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        original = inserir(original, x);
    }

    extrair(original);                       // chaves ordenadas (únicas)
    No* nova = construir(0, qtd - 1);

    bool primeiro = true;
    preOrdem(nova, primeiro);
    cout << "\n";
    cout << altura(original) << " " << altura(nova) << endl;
    return 0;
}