#include <iostream>
#include <cstring>
using namespace std;

int N, M;
int C[301][21];
int dp[301][21];
int ans[301][21];

int DFS(int n, int sum) {
    if(n == M) return 0;
    int& sol = dp[sum][n];
    if(sol != -1) return sol;
    sol = 0;
    for(int i = 0; i <= N - sum; ++i) {
        int temp = DFS(n + 1, sum + i) + C[i][n];
        if(sol < temp) {
            sol = temp;
            ans[sum][n] = i;
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
        for(int j = 0; j < M; ++j)
            cin >> C[fund][j];
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