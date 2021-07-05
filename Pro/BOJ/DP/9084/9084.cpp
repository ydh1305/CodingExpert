#include <iostream>
#include <cstring>
using namespace std;

int N, M;
int arr[21];
int dp[21][10001];

int DFS(int n, int sum) {
    if(sum == M) return 1;
    if(n == N) return 0;
    int& sol = dp[n][sum];
    if(sol != -1) return sol;
    sol = 0;
    int size = (M - sum) / arr[n];
    for(int i = 0; i <= size; ++i) {
        int num = sum + (arr[n] * i);
        if(num <= M)
            sol = sol + DFS(n + 1, num);
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        memset(dp, -1, sizeof(dp));
        cin >> N;
        for(int i = 0; i < N; ++i)
            cin >> arr[i];
        cin >> M;
        cout << DFS(0, 0) << '\n';
    }
    return 0;
}