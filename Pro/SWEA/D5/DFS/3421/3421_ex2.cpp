#include <iostream>
using namespace std;

int N, M;
bool visit[21];
int dp[21];
int sol;

int DFS(int bit, int n) {
    sol++;
    for(int i = n; i <= N; ++i) {
        if(dp[i] & bit) continue;
        if(visit[i]) continue;
        visit[i] = true;
        DFS(bit | (1 << i), i + 1);
        visit[i] = false;
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N >> M;
        for(int i = 1; i <= N; ++i)
            dp[i] = 0;
        for(int i = 0; i < M; ++i) {
            int x, y; cin >> x >> y;
            dp[x] = dp[x] | (1 << y);
            dp[y] = dp[y] | (1 << x);
        }
        sol = 0;
        DFS(0, 1);
        cout << '#' << t << ' ' << sol << '\n'; 
    }
    return 0;
}