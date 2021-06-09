#include <iostream>
using namespace std;

int N, O, M, W, sol, zero, idx;
int A[1000], OP[4], L[1000];
bool visitA[10], visitOP[5];

int calc(int a, int b, int c) {
    if(b == 1) return a + c;
    if(b == 2) return a - c;
    if(b == 3) return a * c;
    if(b == 4) return a / c;
}

void DFS(int n, int len) {
    if(len + 1 > M || len + 1 >= sol) return;
    if(n == W) {
        sol = len + 1;
        return;
    }
    for(int i = zero; i < idx; ++i) {
        int nlen = len + 1 + L[A[i]];
        if(nlen + 1 > M || nlen + 1 >= sol) continue;
        for(int j = 0; j < O; ++j) {
            int num = calc(n, OP[j], A[i]);
            if(num != W && (nlen + 3 > M || nlen + 3 >= sol)) continue;
            if(num < 0 || num >= 1000) continue;
            if(L[num] > nlen) {
                L[num] = nlen;
                DFS(num, nlen);
            }
        }
    }
}

bool check(void) {
    int cnt = 0;
    if(visitA[W % 10]) cnt++;
    else return false;
    if(W >= 10) {
        if(visitA[(W % 100) / 10]) cnt++;
        else return false;
    }
    if(W >= 100) {
        if(visitA[W / 100]) cnt++;
        else return false;
    }
    sol = cnt;
    return true;
}

void solve(void) {
    if(check()) return;
    if(W == 0) {
        if(visitOP[OP[2]]) {
            sol = 4;
            return;
        }
        if(visitOP[OP[4]]) {
            sol = 5;
            return;
        }
    }
    if(zero != -1) {
        swap(A[0], A[zero]);
        zero = 1;
    }
    else zero = 0;
    idx = N;
    for(int i = zero; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            A[idx] = A[i] * 10 + A[j];
            L[A[idx]] = 2;
            idx++;
        }
    }
    for(int i = zero; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            for(int k = 0; k < N; ++k) {
                A[idx] = A[i] * 100 + A[j] * 10 + A[k];
                L[A[idx]] = 3;
                idx++;
            }
        }
    }
    for(int i = 0; i < idx; ++i)
        DFS(A[i], L[A[i]]);
    if(sol == 999) sol = -1;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N >> O >> M;
        for(int i = 0; i <= 999; ++i)
            L[i] = 999;
        for(int i = 0; i <= 9; ++i)
            visitA[i] = false;
        for(int i = 1; i <= 4; ++i)
            visitOP[i] = false;
        zero = -1;
        for(int i = 0; i < N; ++i) {
            cin >> A[i];
            visitA[A[i]] = true;
            L[A[i]] = 1;
            if(!A[i]) zero = i;
        }
        for(int i = 0; i < O; ++i) {
            cin >> OP[i];
            visitOP[OP[i]] = true;
        }
        cin >> W;
        sol = 999;
        solve();
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}