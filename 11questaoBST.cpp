#include <iostream>
#include <random>
using namespace std;
/* 11ª Questão 2º hackhaton árvores binárias*/
int a[100005];
mt19937 gerador(12345);   // fixei como 12345


void quicksort(int lo, int hi) {
    while (lo < hi) {
       
        int pivo = a[lo + gerador() % (hi - lo + 1)];

        
        
        int lt = lo, i = lo, gt = hi;
        while (i <= gt) {
            if (a[i] < pivo) {
                int t = a[lt]; a[lt] = a[i]; a[i] = t;
                lt++; i++;
            } else if (a[i] > pivo) {
                int t = a[i]; a[i] = a[gt]; a[gt] = t;
                gt--;                 
            } else {
                i++;                 
            }
        }

        
        
        if (lt - lo < hi - gt) {
            quicksort(lo, lt - 1);   
            lo = gt + 1;             
        } else {
            quicksort(gt + 1, hi);  
            hi = lt - 1;              
        }
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    quicksort(0, n - 1);

    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << a[i];
    }
    cout << "\n";
    return 0;
}