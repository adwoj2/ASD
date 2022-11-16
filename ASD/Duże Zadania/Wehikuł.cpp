#include <iostream>
#include <queue>
#include <list>
using namespace std;

int main(){
    int p, k, z;
    cin >> p >> k >> z;

    int dr1, dr2;
    int a, odl = 0, odl2;
    int aktualne_skrzyzowanie;
    int aktualna_droga;
    bool zabronione[p + 1];

    list<int> znaleziona_sciezka;
    queue<int> polozenie;
    queue<int> polozenie2;

    for (int i = 0; i <= p; i++)
        zabronione[i] = false;
    for (int i = 0; i < z; i++) {
        cin >> a;
        zabronione[a] = true;
    }

    int n, m;
    cin >> n >> m;

    int powerbanki[n + 2];
    bool odwiedzone[n + 2];
    int odleglosci[n + 2];
    list<int> drogi[n + 2];
    bool czy_mozliwy_stan[n + 2][p + 1];

    odleglosci[1] = 0;
    for (int i = 2; i <= n; i++)
        odleglosci[i] = -1;         //brak drogi
    for (int i = 0; i <= n; i++)
        odwiedzone[i] = false;

    for (int i = 0; i < m; i++) {
        cin >> dr1 >> dr2;
        drogi[dr1].push_back(dr2);
        drogi[dr2].push_back(dr1);
    }
    for (int i = 1; i <= n; i++)
        cin >> powerbanki[i];

    /*bfs w celu ustalenia czy istnieje ścieżka od 1 do n 
    oraz oznaczenia wszystkich odwiedzonych po drodze 
    elementów poprzez ich odległość od wierzchołka 1 */
    
    polozenie.push(-1);             //atrapa
    polozenie.push(1); 
    odwiedzone[1] = true;
    bool koniec = false, koniec2 = false;
    
    do {
        aktualne_skrzyzowanie = polozenie.front();
        polozenie.pop();
        if (aktualne_skrzyzowanie == -1) {
            if (polozenie.empty()) 
                koniec = true;
            odl++;
            polozenie.push(-1);
        }
        else {
            list<int>::iterator it;
            odleglosci[aktualne_skrzyzowanie] = odl;
            for (it = drogi[aktualne_skrzyzowanie].begin(); it != drogi[aktualne_skrzyzowanie].end(); it++) {
                if (!odwiedzone[*it]) {
                    aktualna_droga = *it;
                    odwiedzone[aktualna_droga] = true;
                    polozenie.push(aktualna_droga);
                }
            }
        }
    } while (aktualne_skrzyzowanie != n && !koniec);

    //rozpatrzenie przypadku kiedy nie ma sciezki od 1 do n
    if (odleglosci[n] == -1) {
        printf("-1");
        return 0;
    }
    //wyczyszczenie tablicy odwiedzone w celu ponownego jej wykorzystania
    for (int i = 0; i <= n; i++)
        odwiedzone[i] = false;

    //wyszukanie skrzyzowan na drodze od 1 do n
    odl2 = odl;
    polozenie2.push(-1);             //atrapa
    polozenie2.push(n); 
    while (polozenie2.front() != 1 && !koniec2) {
        aktualne_skrzyzowanie = polozenie2.front();
        polozenie2.pop();
        if (aktualne_skrzyzowanie == -1) {
            if (polozenie2.empty())
                koniec2 = true;
            odl2--;
            polozenie2.push(-1);
        }
        else {
            znaleziona_sciezka.push_front(aktualne_skrzyzowanie);
            list<int>::iterator it;
            for (it = drogi[aktualne_skrzyzowanie].begin(); it != drogi[aktualne_skrzyzowanie].end(); it++) {
                if (!odwiedzone[*it] && odleglosci[*it] == odl2) {
                    aktualna_droga = *it;
                    odwiedzone[aktualna_droga] = true;
                    polozenie2.push(aktualna_droga);
                    break;
                }
            }
        }
    }
    
    znaleziona_sciezka.push_front(1);//umieszczenie 1 w liscie (algorytm jej nie uwzględnia)
    
    //zapisanie tablicy mozliwych stanow pojazdu poprzez mozliwa energie na danym skrzyzowaniu
    for (int i = 1; i <= odl; i++)
        for (int j = 0; j <= p; j++)
            czy_mozliwy_stan[i][j] = false;
    czy_mozliwy_stan[1][p] = true;
    for (int i = 1; i <= odl; i++)
        for (int j = 0; j <= p; j++)
            if (czy_mozliwy_stan[i][j]) {
                if (j - k >= 0) {
                    czy_mozliwy_stan[i + 1][j - k] = true;
                    if (j - k + powerbanki[i + 1] <= p && j - k + powerbanki[i + 1] >= 0)
                        if (!zabronione[j - k + powerbanki[i + 1]])
                            czy_mozliwy_stan[i + 1][j - k + powerbanki[i + 1]] = true;
                }
            }

    int max_bateria = p;
    int ilosc_ladowan = 0;
    list<int> lista_ladowan;

    //ustalenie maksymalnej energii 
    while (max_bateria >= 0 && !czy_mozliwy_stan[odl][max_bateria])
        max_bateria--;
    //przypadek kiedy wehikuł nie jest w stanie osiągnąć żadnej ilości
    //energii na koncowym skrzyzowaniu (wyladowuje sie przed dotarciem do celu)
    if (max_bateria == -1)
        printf("-1");
    else { //algorytm ktory na podstawie mozliwych stanow szuka mozliwych energii 
        //jakie posiadal wehikul na kazdym skrzyzowaniu na trasie zapisujac miejsca ladowania
        int optymalna_trasa = max_bateria;
        for (int i = odl - 1; i > 0; i--)
        {
            if (optymalna_trasa + k <= p)
                if (czy_mozliwy_stan[i][optymalna_trasa + k]) { //dotarło z wyładowania
                    optymalna_trasa += k;
                    continue;        
                }
            if (optymalna_trasa + k - powerbanki[i + 1] >= 0 && optymalna_trasa + k - powerbanki[i + 1] <= p)
                if (czy_mozliwy_stan[i][optymalna_trasa + k - powerbanki[i + 1]]) {
                    lista_ladowan.push_front(i + 1);
                    ilosc_ladowan++;
                    optymalna_trasa = optymalna_trasa + k - powerbanki[i + 1];
            }
        }
        //wypisanie uzyskanych danych
        int znaleziona_sciezka_tab[odl + 1];
        int iter = 0;
        printf("%d %d %d\n", odl, max_bateria, ilosc_ladowan);
        while (!znaleziona_sciezka.empty()) {
            iter++;
            znaleziona_sciezka_tab[iter] = znaleziona_sciezka.front();
            znaleziona_sciezka.pop_front();
            printf("%d ", znaleziona_sciezka_tab[iter]);
        }
        printf("\n");
        while (!lista_ladowan.empty()) {
            int ladowanie = lista_ladowan.front();
            lista_ladowan.pop_front();
            printf("%d ", znaleziona_sciezka_tab[ladowanie]);
        }
    }
}