#include <iostream>
using namespace std;
/* 8ª Questão 2º hackhaton árvores binárias*/
int v[2000];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> v[i];

    long long comparacoes = 0, trocas = 0;

    for (int i = 0; i <= n - 2; i++) {
        int menor = i;                      
        for (int j = i + 1; j < n; j++) {
            comparacoes++;                   
            if (v[j] < v[menor]) menor = j;  
        }
        if (menor != i) {                    
            int aux = v[i];
            v[i] = v[menor];
            v[menor] = aux;
            trocas++;
        }
    }

    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << v[i];
    }
    cout << "\n";
    cout << comparacoes << " " << trocas << endl;
    return 0;
}