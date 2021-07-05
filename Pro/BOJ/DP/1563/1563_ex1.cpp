#include <iostream>
#include <cstring>
using namespace std;

#define MOD 1000000

int N;
int dp[1000][3][4];

int DFS(int n, int a, int b) {
    if(a == 2 || b == 3) return 0;
    if(n == N) return 1;
    int& sol = dp[n][a][b];
    if(sol != -1) return sol;
    sol = 0;
    sol = (sol + DFS(n + 1, a, 0)) % MOD;
    sol = (sol + DFS(n + 1, a + 1, 0)) % MOD;
    sol = (sol + DFS(n + 1, a, b + 1)) % MOD;
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    memset(dp, -1, sizeof(dp));
    cout << DFS(0, 0, 0) << '\n';
    return 0;
}