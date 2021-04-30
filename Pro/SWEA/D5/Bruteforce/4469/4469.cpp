#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007
int A[100001];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int N; cin >> N;
        long long sol = 0;
        long long tmp;
        for(int j = 0; j < N; j++) cin >> A[j];
        for(int j = 0; j < N - 1; j++) {
            long long x; cin >> x;
            if(A[j] && A[j + 1]) {
                cout << "test " << A[j] << ' ' << A[j + 1] << '\n';
                tmp = ((A[j] + x) * (A[j + 1] + x) - x) % MOD;
                sol = (sol * tmp) % MOD;
            } else if(A[j] && !A[j + 1]) {
                tmp = ((A[j] + x - 1) * x) % MOD;
                sol = (sol * tmp) % MOD;
            } else if(!A[j] && A[j + 1]) {
                tmp = (x * (A[j + 1] + x - 1)) % MOD;
                sol = (sol * tmp) % MOD;
            } else {
                tmp = (x * (x - 1)) % MOD;
                sol = (sol * tmp) % MOD;
            }
        }
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}