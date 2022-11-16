#include <iostream>
#include <list>
using namespace std;

int main() {
    int n;
    cin >> n;
    int t[n];
    for (int i = 0; i < n; i++)
        cin >> t[i];
    int max = 0;
    list<int> granice;


    for (int i = 1; i <= n; i++) {
        if (t[i - 1] > max) {
            max = t[i - 1];
        }
        if (i == max) {
            granice.push_back(max);
            max = 0;
        }
    }
    printf("%d\n", granice.size());
    int wypisz = 0;
    wypisz = granice.front();
    granice.pop_front();
    printf("%d", wypisz);
    for (int i = 1; i <= n; i++) {
        printf(" %d", i);
        if (i == wypisz && i != n) {
            wypisz = granice.front();
            granice.pop_front();
            printf("\n%d", wypisz - i);
        }
    }
}