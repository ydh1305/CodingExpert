#include <iostream>
#include <cstring>
using namespace std;

int N, sol;
int arr[9];
int dp[9][1 << 9][1 << 9];

int DFS(int n, int rbit, int lbit, int left, int right) {
    if(n == N) return 1;
    int& sol = dp[n][rbit][lbit];
    if(sol != -1) return sol;
    sol = 0;
    for(int i = 0; i < N; ++i) {
        if((rbit & (1 << i)) || (lbit & (1 << i))) continue;
        if(left + arr[i] >= right)
            sol = sol + DFS(n + 1, rbit | (1 << i), lbit, left + arr[i], right);
        if(left >= right + arr[i])
            sol = sol + DFS(n + 1, rbit, lbit | (1 << i), left, right + arr[i]);
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N;
        for(int i = 0; i < N; ++i)
            cin >> arr[i];
        memset(dp, -1, sizeof(dp));
        cout << '#' << t << ' ' << DFS(0, 0, 0, 0, 0) << '\n';
    }
    return 0;
}