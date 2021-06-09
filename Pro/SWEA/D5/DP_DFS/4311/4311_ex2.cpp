#include <iostream>
using namespace std;

int N, O, M, zero, W, sol, idx;
int arr[1000], op[4], len[1000];
bool visitA[10], visitO[5];

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

int calc(int a, int o, int b) {
    if(o == 1) return a + b;
    if(o == 2) return a - b;
    if(o == 3) return a * b;
    if(o == 4) return a / b;
}

void DFS(int n, int l) {
    if(l + 1 > M || l + 1 >= sol) return;
    if(n == W) {
        sol = l + 1;
        return;
    }
    for(int i = zero; i < idx; ++i) {
        int nlen = l + 1 + len[arr[i]];
        if(nlen + 1 > M || nlen + 1 >= sol) continue;
        for(int j = 0; j < O; ++j) {
            int num = calc(n, op[j], arr[i]);
            if(num <= 0 || num >= 1000) continue;
            if(num != W && (nlen + 3 > M || nlen + 3 >= sol)) continue;
            if(len[num] > nlen) {
                len[num] = nlen;
                DFS(num, nlen);
            }
        }
    }
}

void solve(void) {
    if(check()) return;
    if(W == 0) {
        if(visitO[2]) {
            sol = 4;
            return;
        }
        if(visitO[4]) {
            sol = 5;
            return;
        }
    }
    if(zero != -1) {
        swap(arr[0], arr[zero]);
        zero = 1;
    }
    else zero = 0;
    idx = N;
    for(int i = zero; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            arr[idx] = arr[i] * 10 + arr[j];
            len[arr[idx]] = 2;
            idx++;
        }
    }
    for(int i = zero; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            for(int k = 0; k < N; ++k) {
                arr[idx] = arr[i] * 100 + arr[j] * 10 + arr[k];
                len[arr[idx]] = 3;
                idx++;
            }
        }
    }
    for(int i = 0; i < idx; ++i)
        DFS(arr[i], len[arr[i]]);
    if(sol == 999) sol = -1;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N >> O >> M;
        zero = -1;
        for(int i = 0; i < 1000; ++i)
            len[i] = 999;
        for(int i = 0; i <= 9; ++i)
            visitA[i] = false;
        for(int i = 1; i <= 4; ++i)
            visitO[i] = false;
        for(int i = 0; i < N; ++i) {
            cin >> arr[i];
            visitA[arr[i]] = true;
            len[arr[i]] = 1;
            if(!arr[i]) zero = i;
        }
        for(int i = 0; i < O; ++i) {
            cin >> op[i];
            visitO[op[i]] = true;
        }
        cin >> W;
        sol = 999;
        solve();
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}