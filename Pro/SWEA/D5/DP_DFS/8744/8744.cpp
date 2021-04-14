#include <bits/stdc++.h>
using namespace std;

#define MAX 10010
int N, M;
vector<int> v[MAX];
vector<bool> visit(MAX);

int DFS(vector<vector<int>> dp, int cur, int n) {
    if(n == N - 1) return 0;
    if(dp[n][cur] != -1) return dp[n][cur];
    dp[n][cur] = 0;
    for(int i = 0; i < v[cur].size(); i++) {
        int next = v[cur][i];
        if(visit[next] == true) continue;
        visit[next] = true;
        dp[n][cur] = max(dp[n][cur], DFS(dp, next, n + 1) + 1);
        visit[next] = false;
    }
    return dp[n][cur];
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N >> M;
        int check[MAX] = { 0, };
        for(int j = 0; j < M; j++) {
            int a, b; cin >> a >> b;
            check[a] = b; check[b] = a;
        }
        visit.clear();
        vector<vector<int>> dp(N + 2, vector<int>(N + 2, -1));
        for(int j = 1; j <= N; j++) v[j].clear();
        for(int j = 1; j <= N; j++) {
            for(int k = 1; k <= N; k++) {
                if(j == k) continue;
                if(check[j] == k || check[k] == j) continue;
                v[j].push_back(k);
            }
        }
        visit[1] = true;
        int sol = DFS(dp, 1, 0);
        long long total = ((long long)(N * (N - 1)) / 2) - M - sol;
        cout << '#' << i << ' ' << total << '\n';
    }
    return 0;
}