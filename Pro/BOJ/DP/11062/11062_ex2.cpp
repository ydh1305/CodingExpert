#include <iostream>
#include <cstring>
using namespace std;

int N;
int arr[1000];
int dp[1000][1000];

int DFS(int s, int e, bool stat) {
    if(s > e) return 0;
    int& sol = dp[s][e];
    if(sol != -1) return sol;
    sol = 0;
    if(!stat)
        sol = max(DFS(s + 1, e, 1) + arr[s], DFS(s, e - 1, 1) + arr[e]);
    else
        sol = min(DFS(s, e - 1, 0), DFS(s + 1, e, 0));
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
        cout << DFS(0, N - 1, 0) << '\n';
    }
    return 0;
}