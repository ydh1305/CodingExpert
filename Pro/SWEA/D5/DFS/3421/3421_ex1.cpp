#include <bits/stdc++.h>
using namespace std;

int check[21];
int N, M, sol;

void DFS(int n, int val) {
    if(n == N + 1) {
        sol++;
        return;
    }
    DFS(n + 1, val);
    if(!(check[n] & val)) {
        val = val + (1 << n);
        DFS(n + 1, val);
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N >> M;
        memset(check, 0, sizeof(check));
        for(int j = 0; j < M; j++) {
            int a, b; cin >> a >> b;
            check[a] = check[a] | (1 << b);
            check[b] = check[b] | (1 << a);
        }
        sol = 0;
        DFS(1, 0);
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}