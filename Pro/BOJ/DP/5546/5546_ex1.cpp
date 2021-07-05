#include <iostream>
#include <cstring>
using namespace std;

const int MOD = 10000;

int N, K;
char arr[101];
int dp[101][4][4];

int DFS(int n, int cur, int cnt) {
    if(cnt == 3) return 0;
    if(n == N + 1) return 1;
    int& sol = dp[n][cur][cnt];
    if(sol != -1) return sol;
    sol = 0;
    if(arr[n]) {
        if(cur == arr[n])
            sol = (sol + DFS(n + 1, arr[n], cnt + 1)) % MOD;
        else
            sol = (sol + DFS(n + 1, arr[n], 1)) % MOD;
    }
    else {
        for(int i = 1; i <= 3; ++i) {
            if(cur == i)
                sol = (sol + DFS(n + 1, i, cnt + 1)) % MOD;
            else
                sol = (sol + DFS(n + 1, i, 1)) % MOD;
        }
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> K;
    memset(dp, -1, sizeof(dp));
    for(int i = 0; i < K; ++i) {
        int a, b; cin >> a >> b;
        arr[a] = b;
    }
    cout << DFS(1, 0, 0) << '\n';
    return 0;
}