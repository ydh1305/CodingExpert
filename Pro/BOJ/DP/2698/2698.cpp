#include <iostream>
#include <cstring>
using namespace std;

int N, K;
int dp[101][2][101];

int DFS(int n, int prev, int sum) {
    if(n == N) {
        if(sum == K) return 1;
        return 0;
    }
    int& sol = dp[n][prev][sum];
    if(sol != -1) return sol;
    sol = 0;
    if(prev) {
        if(sum + 1 <= K)
            sol = sol + DFS(n + 1, 1, sum + 1);
        sol = sol + DFS(n + 1, 0, sum);
    }
    else {
        sol = sol + DFS(n + 1, 1, sum);
        sol = sol + DFS(n + 1, 0, sum);
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N >> K;
        memset(dp, -1, sizeof(dp));
        cout << DFS(0, 0, 0) << '\n';
    }
    return 0;
}