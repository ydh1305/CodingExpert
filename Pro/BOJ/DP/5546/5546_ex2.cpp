#include <iostream>
#include <cstring>
using namespace std;

#define MOD 10000

int N, K;
int arr[101];
int dp[101][4][4][4];

int DFS(int n, int a, int b, int c) {
    if(a == 3 || b == 3 || c == 3) return 0;
    if(n == N + 1) return 1;
    int& sol = dp[n][a][b][c];
    if(sol != -1) return sol;
    sol = 0;
    if(arr[n]) {
        if(arr[n] == 1)
            sol = (sol + DFS(n + 1, a + 1, 0, 0)) % MOD;
        else if(arr[n] == 2)
            sol = (sol + DFS(n + 1, 0, b + 1, 0)) % MOD;
        else if(arr[n] == 3)
            sol = (sol + DFS(n + 1, 0, 0, c + 1)) % MOD;
    } else {
        sol = (sol + DFS(n + 1, a + 1, 0, 0)) % MOD;
        sol = (sol + DFS(n + 1, 0, b + 1, 0)) % MOD;
        sol = (sol + DFS(n + 1, 0, 0, c + 1)) % MOD;
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> K;
    for(int i = 0; i < K; ++i) {
        int a, b; cin >> a >> b;
        arr[a] = b;
    }
    memset(dp, -1, sizeof(dp));
    cout << DFS(1, 0, 0, 0) << '\n';
    return 0;
}