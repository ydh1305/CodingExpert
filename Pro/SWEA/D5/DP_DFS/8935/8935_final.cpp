#include <bits/stdc++.h>
using namespace std;

int A[3001], B[101];
int dp[3001][101][101][2];
int N, M;

int DFS(int selN, int selM, int skipM, int sel) {
    if(selN == N && (selM + skipM) == M) return 0;
    int& sol = dp[selN][selM][skipM][sel];
    if(sol != -1) return sol;
    sol = 0;
    if(sel) {
        if(selN < N) {
            sol = max(sol, DFS(selN + 1, selM, skipM, 0) + A[selN]);
            sol = max(sol, DFS(selN + 1, selM, skipM, 1));
        }
        if(selM + skipM < M) {
            sol = max(sol, DFS(selN, selM + 1, skipM, 0) + B[selM]);
            sol = max(sol, DFS(selN, selM, skipM + 1, 1));
        }
    } else {
        if(selN < N)
            sol = max(sol, DFS(selN + 1, selM, skipM, 1));
        if(selM + skipM < M)
            sol = max(sol, DFS(selN, selM, skipM + 1, 1));
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N;
        for(int j = 0; j < N; j++)
            cin >> A[j];
        cin >> M;
        for(int j = 0; j < M; j++)
            cin >> B[j];
        memset(dp, -1, sizeof(dp));
        sort(B, B + M, greater<int>());
        cout << '#' << i << ' ' << DFS(0, 0, 0, 1) << '\n';
    }
    return 0;
}