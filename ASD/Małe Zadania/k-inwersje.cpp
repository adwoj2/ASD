#include <iostream>
#define mod 1000000000
#define kmax 10
using namespace std;

long long int znajdz_w_drzewie(long long int t[], int x, int n, int l, int p, int index) {
    //printf("l:%d, p:%d\n", l, p);
    if(l == p)
        if(x == p)
            return t[index];
        else
            return 0;

    int srodek = (p - l + 1) / 2 + l;
    if (x < srodek) {
        long long int wynik = t[index * 2 + 1];
        return wynik + znajdz_w_drzewie(t, x, n, l, srodek - 1, index * 2);
    } else {
        return znajdz_w_drzewie(t, x, n, srodek, p, index * 2 + 1);
    }
}


int main() {
    int n, k, x;
    cin >> n >> k;
    int a = 1;
    while(a < n)
        a *= 2;
    long long int drzewo[2 * a];
    long long int wartosci[n + 1];
    long long int newwartosci[n + 1];
    int t[n];

    for (int i = 0; i <= n; i++)
        wartosci[i] = 1;
    for(int i = 0; i < n; i++)
        cin >> t[i];

    for(int nr = 2; nr <= k; nr++) {
        for (int i = 0; i < 2 * a; i++) {
            drzewo[i] = 0;
        }

        for (int i = 1; i <= n; i++) {
            x = t[i - 1];
            newwartosci[x] = znajdz_w_drzewie(drzewo, x, n, 1, a, 1) % mod;
            int y = a + x - 1;
            while(y > 1) {
                drzewo[y] += wartosci[x];
                y /= 2;
            }
        }
        for(int i = 0; i <= n; i++)
            wartosci[i] = newwartosci[i];
    }
    long long int sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += newwartosci[i];
        sum %= mod;
    }
    cout << sum;
}