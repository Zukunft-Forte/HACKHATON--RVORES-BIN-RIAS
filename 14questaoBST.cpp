#include <iostream>
using namespace std;
/* 14ª Questão 2º hackhaton árvores binárias*/
int v[100005];
int aux[100005];

// Merge sort comum em [l, r)
void mergeSort(int l, int r) {
    if (r - l <= 1) return;
    int m = (l + r) / 2;
    mergeSort(l, m);
    mergeSort(m, r);
    int i = l, j = m, k = l;
    while (i < m && j < r) {
        if (v[i] <= v[j]) aux[k++] = v[i++];
        else aux[k++] = v[j++];
    }
    while (i < m) aux[k++] = v[i++];
    while (j < r) aux[k++] = v[j++];
    for (k = l; k < r; k++) v[k] = aux[k];
}

struct No {
    int chave;
    int tam;        // quantidade de nós da subárvore (inclui ele mesmo)
    No* esq;
    No* dir;
};

int tamanho(No* r) {
    return r == nullptr ? 0 : r->tam;
}

// Constrói BST balanceada com v[l..r], raiz no ponto médio inferior
No* construir(int l, int r) {
    if (l > r) return nullptr;
    int m = (l + r) / 2;
    No* no = new No;
    no->chave = v[m];
    no->esq = construir(l, m - 1);
    no->dir = construir(m + 1, r);
    no->tam = 1 + tamanho(no->esq) + tamanho(no->dir);  // atualiza o tamanho
    return no;
}

// Posição (1 = menor) da pontuação x, ou -1
int posicao(No* raiz, int x) {
    int antes = 0;                 // quantos elementos menores já descartamos
    No* atual = raiz;
    while (atual != nullptr) {
        if (x == atual->chave) {
            return antes + tamanho(atual->esq) + 1;
        } else if (x < atual->chave) {
            atual = atual->esq;
        } else {
            antes += tamanho(atual->esq) + 1;   // esquerda + o próprio nó são menores que x
            atual = atual->dir;
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> v[i];

    mergeSort(0, n);
    No* raiz = construir(0, n - 1);

    cin >> q;
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        cout << posicao(raiz, x) << "\n";
    }
    return 0;
}