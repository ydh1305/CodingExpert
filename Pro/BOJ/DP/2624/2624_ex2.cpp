#include <iostream>
#include <cstring>
using namespace std;

struct Coin {
    int p;
    int n;
};
Coin C[101];

int T, K;
int dp[101][10001];

int DFS(int n, int sum) {
    if(sum == T) return 1;
    if(n == K) return 0;
    int& sol = dp[n][sum];
    if(sol != -1) return sol;
    sol = 0;
    for(int i = 0; i <= C[n].n; ++i) {
        if((C[n].p * i) + sum <= T)
            sol = sol + DFS(n + 1, sum + (C[n].p * i));
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> T >> K;
    for(int i = 0; i < K; ++i)
        cin >> C[i].p >> C[i].n;
    memset(dp, -1, sizeof(dp));
    cout << DFS(0, 0) << '\n';
    return 0;
}