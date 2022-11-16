#include<iostream>
using namespace std;

#define maxv 1000000


typedef struct {
    char stan;
    int ilosc_bialych;
} el;

void yeet_do_drzewa(int l, int p, el drzewo[], char c, int index, int lgranica, int pgranica, char stan, int n) {
    if(stan == 'B') {
        drzewo[index].ilosc_bialych = pgranica - lgranica + 1;
        drzewo[index].stan = stan;
        }
    if(stan == 'C') {
        drzewo[index].ilosc_bialych = 0;
        drzewo[index].stan = stan;
    }
    if(drzewo[index].stan != '?' && stan == '?')
        stan = drzewo[index].stan;
    int srodek = (pgranica - lgranica) / 2 + lgranica;
       //printf("l: %d, p: %d, index: %d, srodek: %d, lgranica: %d, pgranica: %d\n", l, p, index, srodek, lgranica, pgranica);
    int zmiana;
    if(lgranica == l && pgranica == p) {
        if(c == 'C') {
            if(stan == 'C')
                zmiana = 0;
            else if(stan == 'B')
                zmiana = -p + l - 1;
            else
                zmiana = -drzewo[index].ilosc_bialych;
            drzewo[index].stan = 'C';
            /*if(l != p) {
                drzewo[index * 2].stan = 'C';
                drzewo[index * 2 + 1].stan = 'C';
                drzewo[index * 2].ilosc_bialych = 0;
                drzewo[index * 2 + 1].ilosc_bialych = 0;
            }*/
            drzewo[index].ilosc_bialych = 0;

        }
        else {
            if(stan == 'C')
                zmiana = p - l + 1;
            else if (stan == 'B')
                zmiana = 0;
            else
                zmiana = p - l - drzewo[index].ilosc_bialych + 1;
            drzewo[index].stan = 'B';
            /*if(l != p) {
                drzewo[index * 2].stan = 'B';
                drzewo[index * 2 + 1].stan = 'B';
                if(pgranica <= n) {
                    drzewo[index * 2].ilosc_bialych = (p - l + 1) / 2;
                    drzewo[index * 2 + 1].ilosc_bialych = (p - l + 1) / 2;
                }
                else {
                    drzewo[index * 2].ilosc_bialych = (p - l + 1) / 2;
                    drzewo[index * 2 + 1].ilosc_bialych = ((n - l + 1) / 2) - n + p;
                }

            }*/
            drzewo[index].ilosc_bialych = p - l + 1;
        }
        //cout << index;
        while(index > 0){
            index /= 2;
            drzewo[index].ilosc_bialych += zmiana;
        }
        //cout << " zmiana " << zmiana;

    } else {
        if(srodek < l) {
            if(drzewo[index].stan != '?') {
                drzewo[index * 2].stan = drzewo[index].stan;
                drzewo[index * 2].ilosc_bialych = drzewo[index].ilosc_bialych / 2;
            }
            yeet_do_drzewa(l, p, drzewo, c, index * 2 + 1, srodek + 1, pgranica, stan, n);

        }
        else if(srodek >= p) {
            if(drzewo[index].stan != '?') {
                if(drzewo[index].stan == 'C') {
                    drzewo[index * 2 + 1].stan = 'C';
                    drzewo[index * 2 + 1].ilosc_bialych = 0;
                }
                else if(pgranica <= n){
                    drzewo[index * 2 + 1].stan = 'B';
                    drzewo[index * 2 + 1].ilosc_bialych = drzewo[index].ilosc_bialych / 2; 
                }
                else {
                    drzewo[index * 2 + 1].stan = 'B';
                    drzewo[index * 2 + 1].ilosc_bialych = n - srodek;
                }
            }
            yeet_do_drzewa(l, p, drzewo, c, index * 2, lgranica, srodek, stan, n);
        }
        else {
            yeet_do_drzewa(l, srodek, drzewo, c, index * 2, lgranica, srodek, stan, n);
            yeet_do_drzewa(srodek + 1, p, drzewo, c, index * 2 + 1, srodek + 1, pgranica, stan, n);
        }
        //printf("index?: %d\n", index);
        if(drzewo[index].stan != c) 
            drzewo[index].stan = '?';
    }
}


int main() {
    int n, m, a, b, t;
    char c;

    cin >> n >> m;
    int x = 1;
    while (x < n)
        x *= 2;
    el drzewo[2 * x + 1];
    
    for(int i = 0; i < 2 * x + 1; i++) {
        drzewo[i].ilosc_bialych = 0;
        drzewo[i].stan = 'C';
    }

    for(int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        yeet_do_drzewa(a, b, drzewo, c, 1, 1, x, '?', n);
        /*for(int i = 0; i < 2 * x; i++) {
            cout << i << " " << drzewo[i].ilosc_bialych;
            if(drzewo[i].stan == 'B')
                cout << 'B';
            if(drzewo[i].stan == 'C')
                cout << 'C';
            if(drzewo[i].stan == '?')
                cout << '?';
            cout << endl;
        }*/
        cout << drzewo[1].ilosc_bialych << endl;
    }
}