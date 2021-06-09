#include <iostream>
#include <cstring>
using namespace std;

int arr[10];
int dp[10][1 << 9][1 << 9];
int N, sol;

int DFS(int n, int bit_L, int bit_R, int left, int right) {
    if(n == N) return 1;
    int& sol = dp[n][bit_L][bit_R];
    if(sol != -1) return sol;
    sol = 0;
    for(int i = 0; i < N; ++i) {
        if(bit_L & (1 << i) || bit_R & (1 << i)) continue;
        if(left + arr[i] >= right)
            sol = sol + DFS(n + 1, bit_L | (1 << i), bit_R, left + arr[i], right);
        if(left >= right + arr[i])
            sol = sol + DFS(n + 1, bit_L, bit_R | (1 << i), left, right + arr[i]);
    }
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
        cout << '#' << t << ' ' << DFS(0, 0, 0, 0, 0) << '\n';
    }
    return 0;
}