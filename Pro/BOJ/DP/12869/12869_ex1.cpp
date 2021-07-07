#include <iostream>
#include <cstring>
using namespace std;

#define INF 100

int N;
int dp[61][61][61][61];

int DFS(int n, int A, int B, int C) {
    if(A < 0) A = 0;
    if(B < 0) B = 0;
    if(C < 0) C = 0;
    if(A == 0 && B == 0 && C == 0) return n;
    int& sol = dp[n][A][B][C];
    if(sol != -1) return sol;
    sol = INF;
    sol = min(sol, DFS(n + 1, A - 9, B - 3, C - 1));
    sol = min(sol, DFS(n + 1, A - 9, B - 1, C - 3));
    sol = min(sol, DFS(n + 1, A - 3, B - 9, C - 1));
    sol = min(sol, DFS(n + 1, A - 3, B - 1, C - 9));
    sol = min(sol, DFS(n + 1, A - 1, B - 3, C - 9));
    sol = min(sol, DFS(n + 1, A - 1, B - 9, C - 3));
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    int arr[3] = { 0, };
    for(int i = 0; i < N; ++i)
        cin >> arr[i];
    memset(dp, -1, sizeof(dp));
    cout << DFS(0, arr[0], arr[1], arr[2]) << '\n';
    return 0;
}