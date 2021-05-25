#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int dp[3001][101][101][2];
int A[3001], B[101];
int N, M;

int DFS(int selA, int selB, int skipB, int pos) {
    if(selA == N && (selB + skipB == M)) return 0;
    int& sol = dp[selA][selB][skipB][pos];
    if(sol != -1) return sol;
    sol = 0;
    if(pos) {
        if(selA < N) {
            sol = max(sol, DFS(selA + 1, selB, skipB, 0) + A[selA]);
            sol = max(sol, DFS(selA + 1, selB, skipB, 1));
        }
        if(selB + skipB < M) {
            sol = max(sol, DFS(selA, selB + 1, skipB, 0) + B[selB]);
            sol = max(sol, DFS(selA, selB, skipB + 1, 1));
        }
    } else {
        if(selA < N)
            sol = max(sol, DFS(selA + 1, selB, skipB, 1));
        if(selB + skipB < M) {
            sol = max(sol, DFS(selA, selB + 1, skipB, 1));
            sol = max(sol, DFS(selA, selB, skipB + 1, 1));
        }
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N;
        for(int i = 0; i < N; i++)
            cin >> A[i];
        cin >> M;
        for(int i = 0; i < M; i++)
            cin >> B[i];
        sort(B, B + M, greater<int>());
        memset(dp, -1, sizeof(dp));
        cout << '#' << t << ' ' << DFS(0, 0, 0, 1) << '\n';
    }
    return 0;
}