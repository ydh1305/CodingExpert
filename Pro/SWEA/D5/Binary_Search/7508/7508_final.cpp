#include <bits/stdc++.h>
using namespace std;

int A[50], B[50];
int lower_bound(int s, int e, int v) {
    while(s < e) {
        int m = (s + e) / 2;
        if(A[m] < v) s = m + 1;
        else e = m;
    }
    return e;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int N; cin >> N;
        for(int j = 0; j < N; j++)
            cin >> A[j];
        memset(B, 0, sizeof(B));
        sort(A, A + N);
        int M; cin >> M;
        bool check = false;
        for(int j = 0; j < M; j++) {
            int x; cin >> x;
            if(x > A[N - 1]) {
                check = true;
                break;
            }
            B[lower_bound(0, N - 1, x)]++;
        }
        cout << '#' << i << ' ';
        if(check)
            cout << "-1" << '\n';
        else {
            int sol = 0;
            int num = 0, r;
            for(int j = 0; j < N - 1; j++) {
                if(M % (N - j)) r = 1;
                else r = 0;
                num = min(B[j], M / (N - j) + r);
                M = M - num;
                B[j] = B[j] - num;
                B[j + 1] = B[j + 1] + B[j];
                sol = max(sol, num);
            }
            sol = max(sol, M);
            cout << sol << '\n';
        }
    }
    return 0;
}