#include <iostream>

#include <algorithm>

#include <list>

#include <set>

#include <queue>

using namespace std;

typedef struct wsp {
    int x;
    int y;
    set < struct wsp * > sasiedzi;
    int odl_od_0;
    int indeks;
}
wsp;

int odl(wsp a, wsp b) {
    return min(abs(a.x - b.x), abs(a.y - b.y));
}

bool comparatorx(wsp wspolrzedne1, wsp wspolrzedne2) {
    return wspolrzedne1.x < wspolrzedne2.x;
}

bool comparatory(wsp wspolrzedne1, wsp wspolrzedne2) {
    return wspolrzedne1.y < wspolrzedne2.y;
}

struct Comparator {
    bool operator()(wsp & a, wsp & b) {
        return a.odl_od_0 > b.odl_od_0;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);

    std::cin.tie(NULL);

    int n;
    cin >> n;

    wsp koord[n];
    wsp dosort[n];
    set < wsp * > sasiedzi[n];
    
    for (int i = 0; i < n; i++) {
        cin >> koord[i].x >> koord[i].y;
        koord[i].indeks = i;
        dosort[i].x = koord[i].x;
        dosort[i].y = koord[i].y;
        dosort[i].indeks = koord[i].indeks;
    }

    sort(dosort, dosort + n, comparatorx);

    for (int i = 1; i < n; i++) {
        sasiedzi[dosort[i - 1].indeks].insert( & koord[dosort[i].indeks]);
        sasiedzi[dosort[i].indeks].insert( & koord[dosort[i - 1].indeks]);
    }

    sort(dosort, dosort + n, comparatory);

    for (int i = 1; i < n; i++) {
        sasiedzi[dosort[i - 1].indeks].insert( & koord[dosort[i].indeks]);
        sasiedzi[dosort[i].indeks].insert( & koord[dosort[i - 1].indeks]);
    }

    int D[n];
    for (int i = 1; i < n; i++) {
        koord[i].odl_od_0 = 1000000001;
        D[i] = 1000000001;
    }

    koord[0].odl_od_0 = 0;
    D[0] = 0;

    priority_queue < wsp, vector < wsp > , Comparator > lista;

    lista.push(koord[0]);

    while (!lista.empty()) {

        wsp aktualny = lista.top();
        lista.pop();
        if (aktualny.odl_od_0 > D[aktualny.indeks])
            continue;

        for (wsp * sasiad: sasiedzi[aktualny.indeks]) {
            int x = D[aktualny.indeks] + odl(aktualny, * sasiad);
            if (sasiad -> odl_od_0 > x) {
                sasiad -> odl_od_0 = x;
                D[sasiad -> indeks] = x;
                lista.push( * sasiad);
            }

        }
    }

    cout << koord[n - 1].odl_od_0;

}