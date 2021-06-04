#include <iostream>
using namespace std;

#define INF 987654321

int N, K;
int X[501], Y[501];
int dp[501][501];
int dist[501][501];

int DFS(int cur, int s) {
    int& sol = dp[cur][s];
    if(cur == N - 1) return 0;
    if(sol != -1) return sol;
    sol = INF;
    for(int i = 0; i <= K; ++i) {
        int next = cur + i + 1;
        if(next >= N) continue;
        if(s + i > K) continue;
        sol = min(sol, DFS(next, s + i) + dist[cur][next]);
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N >> K;
        for(int i = 0; i < N; ++i)
            cin >> X[i] >> Y[i];
        for(int i = 0; i < N; ++i) {
            for(register int j = 0; j < N; ++j) {
                dp[i][j] = -1;
                dist[i][j] = abs(X[i] - X[j]) + abs(Y[i] - Y[j]);
            }
        }
        cout << '#' << t << ' ' << DFS(0, 0) << '\n';
    }
    return 0;
}