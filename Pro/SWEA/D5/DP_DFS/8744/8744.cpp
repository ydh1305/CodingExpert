#include <bits/stdc++.h>
using namespace std;

const int MAX = 10000;
int N, M;
vector<vector<int>> dp(MAX + 1, vector<int>(MAX + 1, -1));
vector<vector<int>> v(MAX + 1, vector<int>(MAX + 1, 0));

int DFS(vector<bool> &visit, int cur, int n) {
    if(n == N) return 0;
    if(dp[n][cur] != -1) return dp[n][cur];
    dp[n][cur] = 0;
    visit[cur] = true;
    for(int i = 0; i < v[cur].size(); i++) {
        int next = v[cur][i];
        if(!visit[next]) 
            dp[n][cur] = max(dp[n][cur], DFS(visit, next, n + 1) + 1);
    }
    return dp[n][cur];
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N >> M;
        int *check = new int[N + 1];
        for(int j = 0; j < M; j++) {
            int a, b; cin >> a >> b;
            check[a] = b; check[b] = a;
        }
        fill(v.begin(), v.end(), vector<int>(MAX + 1, 0));
        fill(dp.begin(), dp.end(), vector<int>(MAX + 1, -1));
        for(int j = 1; j <= N; j++) {
            for(int k = 1; k <= N; k++) {
                if(j == k) continue;
                if(check[j] == k || check[k] == j) continue;
                v[j].push_back(k);
            }
        }
        vector<bool> visit(N + 1, false);
        int sol = DFS(visit, 1, 0);
        long long total = ((long long)(N * (N - 1)) / 2) - M - sol;
        cout << '#' << i << ' ' << total << '\n';
    }
    return 0;
}