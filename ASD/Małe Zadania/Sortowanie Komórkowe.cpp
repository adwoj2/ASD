#include <iostream>
using namespace std;

int main() {
    int n;
    cin>>n;
    int A[n];
    int t[n][n][2];
    for(int i = 0; i < n; i++) {
        t[i][i][0] = 1;
        t[i][i][1] = 0;
    }
    for(int i = 0; i < n; i++)
        cin>>A[i];
    for(int d = 1; d < n; d++)
        for (int i = 0; i < n - d; i++){
            t[i][i + d][0] = 0;
            t[i][i + d][1] = 0;
            if(A[i] < A[i + 1]) 
                t[i][i + d][0] += t[i + 1][i + d][0];
            if(A[i] < A[i + d])        
                t[i][i + d][0] += t[i + 1][i + d][1];

            if(A[i + d] > A[i + d - 1]) 
                t[i][i + d][1] += t[i][i + d - 1][1];
            if(A[i + d] > A[i])        
                t[i][i + d][1] += t[i][i + d - 1][0];
            t[i][i + d][0] %= 1000000000;
            t[i][i + d][1] %= 1000000000;
        }
    cout<<(t[0][n - 1][0] + t[0][n - 1][1]) % 1000000000;
}