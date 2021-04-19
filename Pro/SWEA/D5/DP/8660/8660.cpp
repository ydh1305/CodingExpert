#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007
long long dp[100001][51];
long long f[51];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    f[0] = 1;
    for(int i = 1; i <= 50; i++)
        f[i] = (f[i - 1] * i) % MOD;
    for(register int i = 2; i <= 100000; i = i + 2) 
        dp[i][2] = 1;
    for(register int i = 3; i <= 100000; i++) {
        for(int j = 3; j <= min(i, 50); j++) {
            dp[i][j] = ((dp[i - 1][j] * (j - 1) % MOD) + dp[i - 1][j - 1]) % MOD;
        }
    }
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int N, K; cin >> N >> K;
        cout << '#' << i << ' ' << (dp[N][K] * f[K]) % MOD << '\n';
    }
    return 0;
}