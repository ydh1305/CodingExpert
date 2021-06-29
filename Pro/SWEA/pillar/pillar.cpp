#include <iostream>
#include <cstring>
using namespace std;

int N, ans;
int arr[50];
int dp[50][1001][1001];

int DFS(int n, int left, int right) {
    if(left > 1000 || right > 1000) return 0;
    if(n == N) {
        if(left == right) {
            ans = max(ans, left);
        }
        return ans;
    }
    int& sol = dp[n][left][right];
    if(sol != -1) return sol;
    sol = 0;
    sol = max(sol, DFS(n + 1, left + arr[n], right));
    sol = max(sol, DFS(n + 1, left, right + arr[n]));
    sol = max(sol, DFS(n + 1, left, right));
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N;
        memset(dp, -1, sizeof(dp));
        for(int i = 0; i < N; ++i)
            cin >> arr[i];
        ans = 0;
        cout << '#' << t << ' ' << DFS(0, 0, 0) << '\n';
    }
    return 0;
}