#include <iostream>
#include <cstring>
using namespace std;

int N, M;
int S[301][21];
int dp[301][21];
int ans[301][21];

int DFS(int mon, int n) {
    if(n == M) return 0;
    int& sol = dp[mon][n];
    if(sol != -1) return sol;
    sol = 0;
    for(int i = 0; i <= N - mon; ++i) {
        int tmp = DFS(mon + i, n + 1) + S[i][n];
        if(sol < tmp) {
            sol = tmp;
            ans[mon][n] = i;
        }
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for(int i = 0; i < N; ++i) {
        int fund; cin >> fund;
        for(int i = 0; i < M; ++i) {
            int x; cin >> x;
            S[fund][i] = x;
        }
    }
    memset(dp, -1, sizeof(dp));
    cout << DFS(0, 0) << '\n';
    int offset = 0;
    for(int i = 0; i < M; ++i) {
        cout << ans[offset][i] << ' ';
        offset = offset + ans[offset][i];
    }
    return 0;
}