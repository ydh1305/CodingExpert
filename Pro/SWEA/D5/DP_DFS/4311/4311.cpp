#include <iostream>
using namespace std;

int N, O, M, W, sol, zero, idx;
int IN[1000], IO[4], L[1000];
bool CN[10], CO[5];

int check(void) {
    int num = W;
    int cnt = 0;
    if(num >= 100) {
        if(CN[num / 100]) cnt++;
        else return 0;
        num = num % 100;
    }
    if(num >= 10) {
        if(CN[num / 10]) cnt++;
        else return 0;
    }
    if(CN[num % 10]) cnt++;
    else return 0;
    sol = cnt;
    return 1;
}

int calc(int a, int b, int o) {
    if(o == 1) return a + b;
    if(o == 2) return a - b;
    if(o == 3) return a * b;
    if(o == 4) return a / b;
}

void DFS(int n, int m) {
    if(m + 1 > M || m + 1 >= sol) return;
    if(n == W) {
        sol = m + 1;
        return;
    }
    for(int i =  zero; i < idx; i++) {
        int cnt = m + 1 + L[IN[i]];
        if(cnt + 1 > M || cnt + 1 >= sol) continue;
        for(int j = 0; j < O; j++) {
            int num = calc(n, IN[i], IO[j]);
            if(num != W && (cnt + 3 > M || cnt + 3 >= sol)) continue;
            if(num <= 0 || num >= 1000) continue;
            if(L[num] > cnt) {
                L[num] = cnt;
                DFS(num, cnt);
            }
        }
    }
}

void solve(void) {
    if(check()) return;
    if(!W) {
        if(CO[2]) {
            sol = 4;
            return;
        }
        if(CO[4]) {
            sol = 5;
            return;
        }
    }
    if(zero != -1) {
        swap(IN[zero], IN[0]);
        zero = 1;
    }
    else zero = 0;
    idx = N;
    for(int i = zero; i < N; i++) {
        for(int j = 0; j < N; j++) {
            IN[idx] = IN[i] * 10 + IN[j];
            L[IN[idx]] = 2;
            idx++;
        }
    }
    for(int i = zero; i < N; i++) {
        for(int j = 0; j < N; j++) {
            for(int k = 0; k < N; k++) {
                IN[idx] = IN[i] * 100 + IN[j] * 10 + IN[k];
                L[IN[idx]] = 3;
                idx++;
            }
        }
    }
    for(int i = 0; i < idx; i++)
        DFS(IN[i], L[IN[i]]);

    if(sol == 999) sol = -1;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        for(int j = 0; j < 1000; j++)
            L[j] = 999;
        for(int j = 0; j < 5; j++)
            CO[j] = 0;
        for(int j = 0; j < 10; j++)
            CN[j] = 0;
        zero = -1;
        cin >> N >> O >> M;
        for(int j = 0; j < N; j++) {
            cin >> IN[j];
            CN[IN[j]] = true;
            L[IN[j]] = 1;
            if(IN[j] == 0) zero = j;
        }
        for(int j = 0; j < O; j++) {
            cin >> IO[j];
            CO[IO[j]] = true;
        }
        cin >> W;
        sol = 999;
        solve();
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}