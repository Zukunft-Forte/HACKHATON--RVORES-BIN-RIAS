#include <iostream>
using namespace std;
/* 10ª Questão 2 hackhaton árvores binárias*/
int a[200005];
int aux[200005];    
long long inversoes = 0; 

// Ordenando o intervalo l, r, com r não incluso
void mergeSort(int l, int r) {
    if (r - l <= 1) return;       
    int m = (l + r) / 2;
    mergeSort(l, m);
    mergeSort(m, r);

    int i = l, j = m, k = l;
    while (i < m && j < r) {
        if (a[i] <= a[j]) {       
            aux[k++] = a[i++];
        } else {
            aux[k++] = a[j++];
            inversoes += m - i;  
        }
    }
    while (i < m) aux[k++] = a[i++];  
    while (j < r) aux[k++] = a[j++];   
    for (k = l; k < r; k++) a[k] = aux[k];  
}

int main() {
    ios::sync_with_stdio(false);  
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    mergeSort(0, n);

    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << a[i];
    }
    cout << "\n" << inversoes << "\n";
    return 0;
}