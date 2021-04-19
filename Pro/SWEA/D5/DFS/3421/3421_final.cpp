#include <bits/stdc++.h>
using namespace std;

int N, M, sol;
int check[21];
bool visit[21];

void DFS(int n, int val) {
    sol++;
    for(int i = n; i <= N; i++) {
        if(visit[i]) continue;
        if(check[i] & val) continue;
        visit[i] = true;
        val = val + (1 << i);
        DFS(i + 1, val);
        val = val - (1 << i);
        visit[i] = false;
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