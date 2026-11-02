#include <iostream>
using namespace std;
/* 1ª Questão 2º hackhaton, árvores binárias*/
int pai[100001];        
bool temFilho[100001];  

int main() {
    int n;
    cin >> n;

    int raiz = 0;
    for (int i = 1; i <= n; i++) {
        cin >> pai[i];
        if (pai[i] == 0) {
            raiz = i;              
        } else {
            temFilho[pai[i]] = true; 
        }
    }

    int folhas = 0;
    for (int i = 1; i <= n; i++) {
        if (!temFilho[i]) folhas++;  
    }

    int internos = n - folhas;       
    cout << raiz << " " << folhas << " " << internos << endl;
    return 0;
}