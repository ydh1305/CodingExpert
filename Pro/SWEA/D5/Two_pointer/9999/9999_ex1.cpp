#include <iostream>
using namespace std;

int S[100001];
int A[100000], B[100000];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int L, N; cin >> L >> N;
        for(int i = 0; i < N; ++i) {
            cin >> A[i] >> B[i];
            S[i + 1] = S[i] + (B[i] - A[i]);
        }
        int s = 0, sol = 0;
        for(int e = 0; e < N; e++) {
            for(; s <= e && A[s] + L <= B[e]; s++) {
                int len = A[s] + L - A[e];
                if(len > 0)
                    sol = max(sol, S[e] - S[s] + len);
                else
                    sol = max(sol, S[e] - S[s]);
            }
        }
        if(s < N)
            sol = max(sol, S[N] - S[s]);
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}