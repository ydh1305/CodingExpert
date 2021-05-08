#include <iostream>
using namespace std;

int N, O, M, W, sol, zero, idx;
int A[1000], B[4], L[1000];
bool cA[10], cB[5];

bool check(void) {
    int cnt = 0;
    if(cA[W % 10]) cnt++;
    else return false;
    if(W >= 10) {
        if(cA[((W % 100) / 10)]) cnt++;
        else return false;
    }
    if(W >= 100) {
        if(cA[W / 100]) cnt++;
        else return false;
    }
    sol = cnt;
    return true;
}

int calc(int a, int o, int b) {
    if(o == 1) return a + b;
    if(o == 2) return a - b;
    if(o == 3) return a * b;
    if(o == 4) return a / b;
}

void DFS(int n, int len) {
    if(len + 1 > M || len + 1 >= sol) return;
    if(n == W) {
        sol = len + 1;
        return;
    }
    for(int i = zero; i < idx; i++) {
        int nlen = len + 1 + L[A[i]];
        if(nlen + 1 > M || nlen + 1 >= sol) continue;
        for(int j = 0; j < O; j++) {
            int num = calc(n, B[j], A[i]);
            if(num <= 0 || num >= 1000) continue;
            if(num != W && (nlen + 3 > M || nlen + 3 >= sol)) continue;
            if(L[num] > nlen) {
                L[num] = nlen;
                DFS(num, nlen);
            }
        }
    }
}

void solve(void) {
    if(check()) return;
    if(W == 0) {
        if(cB[2]) {
            sol = 4;
            return;
        }
        if(cB[4]) {
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
    for(int i = zero; i < N; i++) {
        for(int j = 0; j < N; j++) {
            A[idx] = A[i] * 10 + A[j];
            L[A[idx]] = 2;
            idx++;
        }
    }
    for(int i = zero; i < N; i++) {
        for(int j = 0; j < N; j++) {
            for(int k = 0; k < N; k++) {
                A[idx] = A[i] * 100 + A[j] * 10 + A[k];
                L[A[idx]] = 3;
                idx++;
            }
        }
    }
    for(int i = 0; i < idx; i++)
        DFS(A[i], L[A[i]]);
    if(sol == 999) sol = -1;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N >> O >> M;
        for(int j = 0; j < 1000; j++)
            L[j] = 999;
        for(int j = 0; j < 10; j++)
            cA[j] = false;
        for(int j = 1; j <= 4; j++)
            cB[j] = false;
        zero = -1;
        for(int j = 0; j < N; j++) {
            cin >> A[j];
            cA[A[j]] = true;
            L[A[j]] = 1;
            if(!A[j]) zero = j;
        }
        for(int j = 0; j < O; j++) {
            cin >> B[j];
            cB[B[j]] = true;
        }
        cin >> W;
        sol = 999;
        solve();
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}