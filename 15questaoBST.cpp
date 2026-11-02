#include <iostream>
using namespace std;
/* 15ª Questão 2º hackhaton árvores binárias*/
struct No {
    int chave;
    int freq;      // quantas vezes essa chave aparece
    int altura;    // altura do nó. E folha será = 1
    int total;     // total de ocorrências na subárvore (com repetições)
    No* esq;
    No* dir;
};

int alt(No* n) { return n == nullptr ? 0 : n->altura; }
int tot(No* n) { return n == nullptr ? 0 : n->total; }

// Recalcula altura e total de um nó a partir dos filhos
void atualizar(No* n) {
    int he = alt(n->esq), hd = alt(n->dir);
    n->altura = 1 + (he > hd ? he : hd);
    n->total = n->freq + tot(n->esq) + tot(n->dir);
}


int fator(No* n) {
    return n == nullptr ? 0 : alt(n->esq) - alt(n->dir);
}

No* rotacaoDireita(No* y) {
    No* x = y->esq;
    y->esq = x->dir;
    x->dir = y;
    atualizar(y);   
    atualizar(x);
    return x;       
}

No* rotacaoEsquerda(No* x) {
    No* y = x->dir;
    x->dir = y->esq;
    y->esq = x;
    atualizar(x);
    atualizar(y);
    return y;
}

// Atualiza o nó e, se estiver desbalanceado, apliquei para que sejam feitas as rotações
No* balancear(No* n) {
    atualizar(n);
    int f = fator(n);
    if (f > 1) {                              
        if (fator(n->esq) < 0)                 
            n->esq = rotacaoEsquerda(n->esq);
        return rotacaoDireita(n);
    }
    if (f < -1) {                             
        if (fator(n->dir) > 0)                 
            n->dir = rotacaoDireita(n->dir);
        return rotacaoEsquerda(n);
    }
    return n;
}


No* inserir(No* r, int x) {
    if (r == nullptr) {
        No* p = new No;
        p->chave = x;
        p->freq = 1;
        p->altura = 1;
        p->total = 1;
        p->esq = nullptr;
        p->dir = nullptr;
        return p;
    }
    if (x < r->chave) r->esq = inserir(r->esq, x);
    else if (x > r->chave) r->dir = inserir(r->dir, x);
    else r->freq++;                
    return balancear(r);             
}


No* removerMenor(No* n, No*& menor) {
    if (n->esq == nullptr) {
        menor = n;
        return n->dir;               
    }
    n->esq = removerMenor(n->esq, menor);
    return balancear(n);
}

// Remove UMA ocorrência de x (se existir)
No* removerUma(No* r, int x) {
    if (r == nullptr) return nullptr;            // ausente: nada muda
    if (x < r->chave) {
        r->esq = removerUma(r->esq, x);
    } else if (x > r->chave) {
        r->dir = removerUma(r->dir, x);
    } else {
        if (r->freq > 1) {
            r->freq--;                           // ainda sobra exemplar: só diminui
        } else if (r->esq == nullptr) {          // último exemplar, sem filho esquerdo
            No* filho = r->dir;
            delete r;
            return filho;
        } else if (r->dir == nullptr) {          // último exemplar, sem filho direito
            No* filho = r->esq;
            delete r;
            return filho;
        } else {                                 // último exemplar, dois filhos
            No* suc;                             // sucessor em ordem
            No* novaDir = removerMenor(r->dir, suc);
            r->chave = suc->chave;               // copia chave e frequência do sucessor
            r->freq = suc->freq;
            delete suc;
            r->dir = novaDir;
        }
    }
    return balancear(r);
}

// k-ésima menor ocorrência (1 <= k <= total)
int kesimo(No* r, int k) {
    No* atual = r;
    while (atual != nullptr) {
        int naEsq = tot(atual->esq);
        if (k <= naEsq) {
            atual = atual->esq;                  // está na esquerda
        } else if (k <= naEsq + atual->freq) {
            return atual->chave;                 // está neste nó (nas repetições)
        } else {
            k -= naEsq + atual->freq;            // pula esquerda e este nó
            atual = atual->dir;
        }
    }
    return 0;  // não deve acontecer
}

bool primeiroSaida;

// Lista todas as ocorrências em ordem (cada chave freq vezes)
void listar(No* r) {
    if (r == nullptr) return;
    listar(r->esq);
    for (int i = 0; i < r->freq; i++) {
        if (!primeiroSaida) cout << " ";
        cout << r->chave;
        primeiroSaida = false;
    }
    listar(r->dir);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

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
            raiz = removerUma(raiz, x);
        } else if (cmd == 'K') {
            int k; cin >> k;
            if (k < 1 || k > tot(raiz)) cout << "INVÁLIDO!\n";
            else cout << kesimo(raiz, k) << "\n";
        } else if (cmd == 'L') {
            if (tot(raiz) == 0) {
                cout << "VAZIA\n";
            } else {
                primeiroSaida = true;
                listar(raiz);
                cout << "\n";
            }
        }
    }
    return 0;
}