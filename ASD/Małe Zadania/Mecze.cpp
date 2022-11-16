#include <iostream>
#include <algorithm>
using namespace std;

#define change_bit(a, b) (a |= 1ULL << b)

int main() {
    int a, b;
    int x;
    bool tak;
    int bit = 0;
    long long unsigned int t[40000];
    scanf("%d%d", &a, &b);
    for(int i = 0; i < a; i++)
        t[i] = 0;
    for(int i = 0; i < b; i++) {
        for(int i = 0; i < a / 2; i++) {
            scanf("%d", &x);
            change_bit(t[x - 1], bit);
        }
        for(int i = 0; i < a / 2; i++)
            scanf("%d", &x);
        bit++;
    }
    sort(t, t + a);
    for(int i = 0; i < a - 1; i++) {
        if(t[i] == t[i + 1]) {
            printf("NIE");
            return 0;
        }
    }
    printf("TAK");
}