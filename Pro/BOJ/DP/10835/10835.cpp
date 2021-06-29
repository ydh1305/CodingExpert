#include <iostream>
#include <cstring>
using namespace std;

int N;
int A[2000], B[2000];
int dp[2000][2000];

int DFS(int left, int right) {
    if(left == N || right == N) return 0;
    int& sol = dp[left][right];
    if(sol != -1) return sol;
    sol = 0;
    sol = max(sol, DFS(left + 1, right));
    sol = max(sol, DFS(left + 1, right + 1));
    if(A[left] > B[right])
        sol = max(sol, DFS(left, right + 1) + B[right]);
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    memset(dp, -1, sizeof(dp));
    for(int i = 0; i < N; ++i)
        cin >> A[i];
    for(int i = 0; i < N; ++i)
        cin >> B[i];
    cout << DFS(0, 0);
    return 0;
}