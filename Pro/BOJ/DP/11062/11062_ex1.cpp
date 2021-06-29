#include <iostream>
#include <cstring>
using namespace std;

int N;
int arr[1000];
int dp[1000][1000];

int DFS(int n, int s, int e) {
    if(n == N) return 0;
    int& sol = dp[s][e];
    if(sol != -1) return sol;
    sol = 0;
    if(n % 2)
        sol = min(DFS(n + 1, s + 1, e), DFS(n + 1, s, e - 1));
    else
        sol = max(DFS(n + 1, s + 1, e) + arr[s], DFS(n + 1, s, e - 1) + arr[e]);
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
        cout << DFS(0, 0, N - 1) << '\n';
    }
    return 0;
}