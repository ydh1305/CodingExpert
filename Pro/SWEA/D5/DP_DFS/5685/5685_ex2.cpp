#include <iostream>
using namespace std;

#define MOD 1234567891

int N;
int arr[100];
long long dp[100][21];

long long DFS(int n, int s) {
    if(n == N - 2) {
        if(s == arr[N - 1])
            return 1;
        return 0;
    }
    long long& sol = dp[n][s];
    if(sol != -1) return sol;
    sol = 0;
    if(s + arr[n + 1] <= 20)
        sol = (sol + DFS(n + 1, s + arr[n + 1])) % MOD;
    if(s - arr[n + 1] >= 0)
        sol = (sol + DFS(n + 1, s - arr[n + 1])) % MOD;
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N;
        for(int i = 0; i < N; ++i) {
            cin >> arr[i];
            for(int j = 0; j <= 20; ++j)
                dp[i][j] = -1;
        }
        cout << '#' << t << ' ' << DFS(0, arr[0]) << '\n';    
    }
    return 0;
}