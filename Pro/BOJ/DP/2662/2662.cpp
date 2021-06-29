#include <iostream>
#include <cstring>
using namespace std;

int N, M;
int C[301][20];
int ans[301][20];
int dp[301][20];

int DFS(int invest, int ncom) {
    if(ncom == M) return 0;
    int& sol = dp[invest][ncom];
    if(sol != -1) return sol;
    sol = 0;
    for(int price = 0; price <= (N - invest); ++price) {
        int temp = DFS(invest + price, ncom + 1) + C[price][ncom];
        if(sol < temp) {
            sol = temp;
            ans[invest][ncom] = price;
        }
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for(int i = 0; i < N; ++i) {
        int amount; cin >> amount;
        for(int j = 0; j < M; ++j)
            cin >> C[amount][j];
    }
    memset(dp, -1, sizeof(dp));
    cout << DFS(0, 0) << '\n';
    int offset = 0;
    for(int i = 0; i < M; ++i) {
        cout << ans[offset][i] << ' ';
        offset = offset + ans[offset][i];
    }
    cout << '\n';
    return 0;
}