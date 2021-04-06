#include<iostream>
using namespace std;

#define MOD 1234567891
int N;
int arr[101];
long long dp[101][21];

long long DFS(int n, int s) {
    if(n == N - 2) {
        if(s == arr[N - 1]) return 1;
        return 0;
    }
    if(dp[n][s] != -1) return dp[n][s];
    dp[n][s] = 0;
    if(s + arr[n + 1] <= 20) dp[n][s] = (dp[n][s] + DFS(n + 1, s + arr[n + 1])) % MOD; 
    if(s - arr[n + 1] >= 0) dp[n][s] = (dp[n][s] + DFS(n + 1, s - arr[n + 1])) % MOD; 
    return dp[n][s];
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N;
        for(int j = 0; j < N; j++) cin >> arr[j];
        for(int j = 0; j < N; j++)
            for(int k = 0; k < 21; k++) dp[j][k] = -1;
        cout << '#' << i << ' ' << DFS(0, arr[0]) << '\n';
    }
    return 0;
}
