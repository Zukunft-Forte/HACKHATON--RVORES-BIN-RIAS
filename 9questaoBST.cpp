#include <iostream>
#include <string>
using namespace std;
/* 9ª Questão 2º hackhaton árvores binárias*/
string id[3000];
int nota[3000];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> id[i] >> nota[i];

    long long deslocamentos = 0;

    for (int i = 1; i < n; i++) {
        string chaveId = id[i];      
        int chaveNota = nota[i];
        int j = i - 1;

        // Empurrando para a direita só quem tem nota maior
        while (j >= 0 && nota[j] > chaveNota) {
            id[j + 1] = id[j];
            nota[j + 1] = nota[j];
            deslocamentos++;         // cada movimento conta como 1!
            j--;
        }
        id[j + 1] = chaveId;         
        nota[j + 1] = chaveNota;
    }

    for (int i = 0; i < n; i++) cout << id[i] << " " << nota[i] << "\n";
    cout << "DESLOCAMENTOS " << deslocamentos << endl;
    return 0;
}