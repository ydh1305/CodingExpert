#include <iostream>
#include <cstring>
using namespace std;

int T;
int N, K;
int dp[101][2][101];

int DFS(int n, int prev, int cnt) {
    if(cnt > K || n > N) return 0;
    if(n == N && cnt == K) return 1;
    int& sol = dp[n][prev][cnt];
    if(sol != -1) return sol;
    sol = 0;
    if(!prev) {
        sol = sol + DFS(n + 1, 1, cnt);
        sol = sol + DFS(n + 1, 0, cnt);
    }
    else {
        sol = sol + DFS(n + 1, 1, cnt + 1);
        sol = sol + DFS(n + 1, 0, cnt);
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> T;
    for(int i = 0; i < T; ++i) {
        cin >> N >> K;
        memset(dp, -1, sizeof(dp));
        cout << DFS(0, 0, 0) << '\n';
    }

    return 0;
}