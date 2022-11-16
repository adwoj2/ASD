#include <iostream>
#include <stdio.h>
#define NMAX 1000000
using namespace std;

int main() {
    int n, x, k;
    long a, b;
    int prevodd = -1, preveven = -1, nexteven = -1, nextodd = -1;
    bool sumodd;
    scanf("%d", &n);
    int A[NMAX];
    unsigned long long S[NMAX + 1];
    unsigned long long sum = 0;
    int P[NMAX];
    int N[NMAX];
    for(int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }
    for(int i = 0; i < n; i++) {
        sum += A[n - i - 1];
        S[i + 1] = sum;
    }
    for(int i = 0; i < n; i++) {
        if(A[i] % 2 == 0) {
            preveven = A[i];
            P[i] = prevodd;
        }
        if(A[i] % 2 == 1) {
            prevodd = A[i];
            P[i] = preveven;
        }
    }
    for(int i = n - 1; i >= 0; i--) {
        if(A[i] % 2 == 0) {
            nexteven = A[i];
            N[i] = nextodd;
        }
        if(A[i] % 2 == 1) {
            nextodd = A[i];
            N[i] = nexteven;
        }
    }
    cin>>x;
    for(int i = 0; i < x; i++) {
        cin>>k;
        sumodd = S[k] % 2 == 1;
        if(!sumodd) {
            if(k == n)
                printf("%d\n", -1);
            else {
                if(P[n - k] == -1)
                    a = 1;
                else
                    a = P[n - k] - A[n - k];
                if((A[n - k] - A[n - k - 1]) % 2 == 0) {
                    if(N[n - k] == -1)
                        b = 1;
                    else
                        b = A[n - k - 1] - N[n - k]; 
                }
                else {
                    if(N[n - k] == -1 || P[n - k - 1] == -1)
                        b = 1;
                    else
                        b = P[n - k - 1] - N[n - k];
                }
                if(a == 1 && b == 1)
                    printf("%d\n", -1);
                else if(a == 1)
                    printf("%llu\n", S[k] + b);
                else if(b == 1)
                    printf("%llu\n", S[k] + a);
                else if(a <= b)
                    printf("%llu\n", S[k] + b);
                else if(a > b)
                    printf("%llu\n", S[k] + a);
            }
        } else
        printf("%llu\n", S[k]);
    }
}