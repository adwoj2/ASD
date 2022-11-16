#include <iostream>
#include <list>
using namespace std;


void znajdz_najglebszy_w(int v, int n, int syn[][2], int najglebsze[], int najglebszy_el[]) {
    if(syn[v][0] == -1 && syn[v][1] == -1) {
        najglebsze[v] = 0;
        najglebszy_el[v] = v;
    } else {
        if(syn[v][1] != -1)
            if(najglebsze[syn[v][1]] == -1)
                znajdz_najglebszy_w(syn[v][1], n, syn, najglebsze, najglebszy_el);
        if(syn[v][0] != -1)
            if(najglebsze[syn[v][0]] == -1)
                znajdz_najglebszy_w(syn[v][0], n, syn, najglebsze, najglebszy_el);
        if(syn[v][1] == -1) {
            najglebsze[v] = najglebsze[syn[v][0]] + 1;
            najglebszy_el[v] = najglebszy_el[syn[v][0]];
        }
        else if(syn[v][0] == -1) {
            najglebsze[v] = najglebsze[syn[v][1]] + 1;
            najglebszy_el[v] = najglebszy_el[syn[v][1]];
        }
        else {
            najglebsze[v] = max(najglebsze[syn[v][0]], najglebsze[syn[v][1]]) + 1;
            if(najglebsze[syn[v][0]] > najglebsze[syn[v][1]])
                najglebszy_el[v] = najglebszy_el[syn[v][0]];
            else
                najglebszy_el[v] = najglebszy_el[syn[v][1]];
        }
    }
}

void znajdz_najglebszy_poza(int v, int n, int rodzic[], int syn[][2], int najglebszy_el[], int najglebsze[], int najglebsze_poza[], int najglebszy_el_poza[]) {

    if(rodzic[v] == -1) {
        najglebsze_poza[v] = 0;
        najglebszy_el_poza[v] = v;
    } else {
        if(syn[rodzic[v]][0] != -1 && syn[rodzic[v]][0] != v) {
            najglebsze_poza[v] = max(najglebsze[syn[rodzic[v]][0]] + 2, najglebsze_poza[rodzic[v]] + 1);
            if(najglebsze[syn[rodzic[v]][0]] + 2 > najglebsze_poza[rodzic[v]] + 1)
                najglebszy_el_poza[v] = najglebszy_el[syn[rodzic[v]][0]];
            else
                najglebszy_el_poza[v] = najglebszy_el_poza[rodzic[v]];
        } else if(syn[rodzic[v]][1] != -1){
            najglebsze_poza[v] = max(najglebsze[syn[rodzic[v]][1]] + 2, najglebsze_poza[rodzic[v]] + 1);
            if(najglebsze[syn[rodzic[v]][1]] + 2 > najglebsze_poza[rodzic[v]] + 1)
                najglebszy_el_poza[v] = najglebszy_el[syn[rodzic[v]][1]];
            else
                najglebszy_el_poza[v] = najglebszy_el_poza[rodzic[v]];
        } else {
            najglebsze_poza[v] = najglebsze_poza[rodzic[v]] + 1;
            najglebszy_el_poza[v] = najglebszy_el_poza[rodzic[v]];
        }
    }
    if(syn[v][1] != -1)
        znajdz_najglebszy_poza(syn[v][1], n, rodzic, syn, najglebszy_el, najglebsze, najglebsze_poza, najglebszy_el_poza);
    if(syn[v][0] != -1)
        znajdz_najglebszy_poza(syn[v][0], n, rodzic, syn, najglebszy_el, najglebsze, najglebsze_poza, najglebszy_el_poza);
}


int main() {

    
ios_base::sync_with_stdio(false);

cin.tie(NULL);

    int a, b, n, m, x, y;

    cin >> n;
    int h = 1, n_kopia = n;
    while(n_kopia > 0){
        n_kopia /= 2;
        h++;
    }
    int przodek[n + 1][h];
    for(int i = 0; i < h; i++)
        for(int j = 1; j <= n; j++)
            przodek[j][i] = -1;
    int syn[n + 1][2];
    int wysokosci[n + 1];
    int max_dystans_poddrzewo[n + 1];
    int najdalszy_poddrzewo[n + 1];
    int max_dystans_poza[n + 1];
    int najdalszy_poza[n + 1];
    int max_dystans[n + 1];
    int najdalszy_wierzcholek[n + 1];
    for(int i = 1; i <= n; i++) {
        cin >> a >> b;
        if(a != -1)
            przodek[a][0] = i;
        if(b != -1)
            przodek[b][0] = i;
        syn[i][0] = a;
        syn[i][1] = b; 
    }
    
    list <int> lista;
    lista.push_back(1);
    lista.push_back(-1);
    int iterator = 0;
    while(lista.size() > 1) {
        int x = lista.front();
        lista.pop_front();
        if(x == -1) {
            lista.push_back(-1);
            iterator++;
        } else {
            wysokosci[x] = iterator;
            if(syn[x][0] != -1)
                lista.push_back(syn[x][0]);
            if(syn[x][1] != -1)
                lista.push_back(syn[x][1]);
        }
    }

    for(int i = 1; i < h; i++) {
        list <int> listaprzod;
        listaprzod.push_back(1);
        while(!listaprzod.empty()) {
            int x = listaprzod.front();
            listaprzod.pop_front();
            if(przodek[x][i - 1] != -1 && przodek[przodek[x][i - 1]][i - 1] != -1)
                przodek[x][i] = przodek[przodek[x][i - 1]][i - 1];
            else
                przodek[x][i] = -1;
            if(syn[x][0] != -1)
                listaprzod.push_back(syn[x][0]);
            if(syn[x][1] != -1)
                listaprzod.push_back(syn[x][1]);            
        }
    }

    int najglebsze[n + 1];
    int najglebszy_el[n + 1];
    int najglebsze_poza[n + 1];
    int najglebszy_el_poza[n + 1];
    int absolutnie_najwiekszy[n + 1];
    int absolutnie_najwiekszy_el[n + 1];
    for(int i = 1; i <= n; i++) {
        najglebsze[i] = -1;
        najglebszy_el[i] = -1;
        najglebsze_poza[i] = -1;
        najglebszy_el_poza[i] = -1;
        absolutnie_najwiekszy[i] = -1;
        absolutnie_najwiekszy_el[i] = -1;
    }
    int rodzic[n + 1];

    for(int i = 1; i <= n; i++) {
        rodzic[i] = przodek[i][0];
    }

    znajdz_najglebszy_w(1, n, syn, najglebsze, najglebszy_el);
    znajdz_najglebszy_poza(1, n, rodzic, syn, najglebszy_el, najglebsze, najglebsze_poza, najglebszy_el_poza);

    for(int i = 1; i <= n; i++) {
        if(najglebsze[i] > najglebsze_poza[i]) {
            absolutnie_najwiekszy[i] = najglebsze[i];
            absolutnie_najwiekszy_el[i] = najglebszy_el[i];
        } else {
            absolutnie_najwiekszy[i] = najglebsze_poza[i];
            absolutnie_najwiekszy_el[i] = najglebszy_el_poza[i];
        }
    }

    cin >> m;
    for(int k = 0; k < m; k++) {
        cin >> x >> y;
        if (absolutnie_najwiekszy[x] < y)
            printf("-1\n");
        else if (absolutnie_najwiekszy[x] == y)
            printf("%d\n", absolutnie_najwiekszy_el[x]);
        else {
            int kopia = x;
            int z = absolutnie_najwiekszy_el[x];
            int kopiaz = z;
            int roznica_wysokosci;
            if(wysokosci[kopia] > wysokosci[kopiaz]) {
                roznica_wysokosci = wysokosci[kopia] - wysokosci[kopiaz];
                int o_ile = 0;
                while(roznica_wysokosci > 0){
                    if(roznica_wysokosci % 2 == 1)
                        kopia = przodek[kopia][o_ile];
                    o_ile++;
                    roznica_wysokosci /= 2;
                }
            } else {
                roznica_wysokosci = wysokosci[kopiaz] - wysokosci[kopia];
                int o_ile = 0;
                while(roznica_wysokosci > 0){
                    if(roznica_wysokosci % 2 == 1)
                        kopiaz = przodek[kopiaz][o_ile];
                    o_ile++;
                    roznica_wysokosci /= 2;
                }
            }
            int kolejny_iterator = 0;
            int wspolny_przodek;

            if(kopia == kopiaz) {
                wspolny_przodek = kopia;
            } else {
                while(przodek[kopia][kolejny_iterator] != przodek[kopiaz][kolejny_iterator])
                    kolejny_iterator++;
                int potencjalny_x = przodek[kopia][kolejny_iterator - 1];
                int potencjalny_z = przodek[kopiaz][kolejny_iterator - 1];
                kolejny_iterator--;
                while(przodek[potencjalny_x][0] != przodek[potencjalny_z][0]) {
                    if(przodek[potencjalny_x][kolejny_iterator - 1] == przodek[potencjalny_z][kolejny_iterator - 1])
                        kolejny_iterator--;
                    else {
                        potencjalny_x = przodek[potencjalny_x][kolejny_iterator - 1];
                        potencjalny_z = przodek[potencjalny_z][kolejny_iterator - 1];
                        kolejny_iterator--;
                    } 
                }
                wspolny_przodek = przodek[potencjalny_x][0];
            }
            if(wysokosci[x] - wysokosci[wspolny_przodek] >= y) {
                int o_ile2 = 0;
                while(y > 0){
                    if(y % 2 == 1)
                        x = przodek[x][o_ile2];
                    y /= 2;
                    o_ile2++;
                }
                printf("%d\n", x);
            } else {
                int nowa_ilosc = absolutnie_najwiekszy[x] - y;
                int o_ile2 = 0;
                while(nowa_ilosc > 0){
                    if(nowa_ilosc % 2 == 1)
                        z = przodek[z][o_ile2];
                    nowa_ilosc /= 2;
                    o_ile2++;
                }
                printf("%d\n", z);
            }
        }
    }
}