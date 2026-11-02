#include <iostream>
#include <vector>
using namespace std;
/* 13ª Questão 2º hackhaton árvores binárias*/
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
        if (c == atual->chave) return raiz;     // repetida: ignora
        if (c < atual->chave) {
            if (atual->esq == nullptr) { atual->esq = novoNo(c); return raiz; }
            atual = atual->esq;
        } else {
            if (atual->dir == nullptr) { atual->dir = novoNo(c); return raiz; }
            atual = atual->dir;
        }
    }
}

bool buscar(No* raiz, int c) {
    No* atual = raiz;
    while (atual != nullptr) {
        if (c == atual->chave) return true;
        if (c < atual->chave) atual = atual->esq;
        else atual = atual->dir;
    }
    return false;
}

No* minimo(No* r) {
    while (r->esq != nullptr) r = r->esq;
    return r;
}

No* remover(No* raiz, int c) {
    if (raiz == nullptr) return nullptr;        // se estiver vazio, nada acontece
    if (c < raiz->chave) {
        raiz->esq = remover(raiz->esq, c);
    } else if (c > raiz->chave) {
        raiz->dir = remover(raiz->dir, c);
    } else {
        if (raiz->esq == nullptr) {
            No* filho = raiz->dir;
            delete raiz;
            return filho;
        }
        if (raiz->dir == nullptr) {
            No* filho = raiz->esq;
            delete raiz;
            return filho;
        }
        No* suc = minimo(raiz->dir);            // coloquei para que seja sucedido em ordem
        raiz->chave = suc->chave;
        raiz->dir = remover(raiz->dir, suc->chave);
    }
    return raiz;
}


void faixa(No* r, int a, int b, vector<int>& saida) {
    if (r == nullptr) return;
    if (a < r->chave) faixa(r->esq, a, b, saida);   
    if (a <= r->chave && r->chave <= b) saida.push_back(r->chave);
    if (r->chave < b) faixa(r->dir, a, b, saida);   
}

int main() {
    int q;
    cin >> q;
    No* raiz = nullptr;

    for (int i = 0; i < q; i++) {
        char cmd;
        cin >> cmd;
        if (cmd == 'I') {
            int x; cin >> x;
            raiz = inserir(raiz, x);
        } else if (cmd == 'R') {
            int x; cin >> x;
            raiz = remover(raiz, x);
        } else if (cmd == 'B') {
            int x; cin >> x;
            cout << (buscar(raiz, x) ? "SIM" : "NÃO") << "\n";
        } else if (cmd == 'F') {
            int a, b; cin >> a >> b;
            vector<int> saida;
            faixa(raiz, a, b, saida);
            if (saida.empty()) {
                cout << "VAZIA NO MOMENTO\n";
            } else {
                for (size_t k = 0; k < saida.size(); k++) {
                    if (k > 0) cout << " ";
                    cout << saida[k];
                }
                cout << "\n";
            }
        }
    }
    return 0;
}