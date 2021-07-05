#include <iostream>
#include <cstring>
using namespace std;

struct Coin {
    int p;
    int c;
};
Coin C[100];

int T, K;
int dp[101][10001];

int DFS(int n, int sum) {
    if(sum == T) return 1;
    if(n == K) return 0;
    int& sol = dp[n][sum];
    if(sol != -1) return sol;
    sol = 0;
    for(int i = 0; i <= C[n].c; ++i) {
        if(sum + (C[n].p * i) <= T)
            sol = sol + DFS(n + 1, sum + (C[n].p * i));
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> T >> K;
    memset(dp, -1, sizeof(dp));
    for(int i = 0; i < K; ++i)
        cin >> C[i].p >> C[i].c;
    cout << DFS(0, 0) << '\n';
    return 0;
}