#include <bits/stdc++.h>
using namespace std;

#define MAX 100001
int S[MAX], A[MAX], B[MAX];

int main(void) { 
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int L, N; cin >> L >> N;      
        for(int j = 0; j < N; j++) {
            cin >> A[j] >> B[j];
            S[j + 1] = S[j] + (B[j] - A[j]); 
        }
        int s = 0;
        int sol = 0;
        for(register int e = 0; e < N; e++) {
            for(; s <= e && A[s] + L <= B[e]; s++) {
                sol = max(sol, S[e] - S[s] + max(A[s] + L - A[e], 0));
            }
        }
        if(s < N) sol = max(sol, S[N] - S[s]);
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}