#include <iostream>
using namespace std;

#define MOD 1234567891

int N;
int arr[101];
long long dp[101][21];

long long DFS(int n, int sum) {
    if(n == N - 1) {
        if(sum == arr[N - 1]) return 1;
        return 0;
    }
    long long& sol = dp[n][sum];
    if(sol != -1) return sol;
    sol = 0;
    int num = sum + arr[n];
    if(num <= 20)
        sol = (sol + DFS(n + 1, num)) % MOD;
    num = sum - arr[n];
    if(num >= 0)
        sol = (sol + DFS(n + 1, num)) % MOD;
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N;
        for(int i = 0; i < N; ++i)
            for(int j = 0; j <= 20; ++j)
                dp[i][j] = -1;
        for(int i = 0; i < N; ++i)
            cin >> arr[i];
        cout << '#' << t << ' ' << DFS(0, 0) << '\n';
    }
    return 0;
}