#include <iostream>
#include <cstring>
using namespace std;

#define INF 987654321

int N;
int X[12], Y[12];
int dist[12][12];
int dp[1 << 11][12];

int DFS(int bit, int cur, int cnt) {
    if(cnt == N) return dist[cur][N + 1];
    int& sol = dp[bit][cur];
    if(sol != -1) return sol;
    sol = INF;
    for(int i = 1; i <= N; ++i) {
        if(bit & (1 << i)) continue;
        sol = min(sol, DFS(bit | (1 << i), i, cnt + 1) + dist[cur][i]);
    }
    return sol;
}   

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N;
        for(register int i = 0; i <= (1 << N + 1); ++i)
            for(int j = 0; j < N + 2; ++j)
                dp[i][j] = -1;
        cin >> X[0] >> Y[0];
        cin >> X[N + 1] >> Y[N + 1];
        for(int i = 1; i <= N; ++i)
            cin >> X[i] >> Y[i];
        for(int i = 0; i <= N + 1; ++i)
            for(int j = 0; j <= N + 1; ++j)
                dist[i][j] = abs(X[i] - X[j]) + abs(Y[i] - Y[j]);
        cout << '#' << t << ' ' << DFS(1, 0, 0) << '\n';
    }
    return 0;
}