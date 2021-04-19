#include <bits/stdc++.h>
using namespace std;

#define MAX 500
int dp[MAX + 1][MAX + 1];
int X[MAX], Y[MAX];
int N, M;

int get_distance(int cur, int next) {
    return (abs(X[cur] - X[next]) + abs(Y[cur] - Y[next]));
}

int DFS(int cur, int k) {
    if(cur == N - 1) return 0;
    int& sol = dp[cur][k];
    if(sol != -1) return sol;
    sol = INT_MAX;
    for(int i = 0; i <= M; i++) {
        int next = cur + i + 1;
        if(next >= N) continue;
        if(k + i > M) continue;
        sol = min(sol, DFS(next, k + i) + get_distance(cur, next));
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N >> M;
        memset(dp, -1, sizeof(dp));
        for(int j = 0; j < N; j++) cin >> X[j] >> Y[j];
        cout << '#' << i << ' ' << DFS(0, 0) << '\n';
    }
    return 0;
}