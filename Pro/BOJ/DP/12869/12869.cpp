#include <iostream>
#include <cstring>
using namespace std;

#define INF 987654321

int N;
int arr[3];
int dp[61][61][61][61];

int DFS(int n, int a, int b, int c) {
    if(a < 0) a = 0;
    if(b < 0) b = 0;
    if(c < 0) c = 0;
    if(a == 0 && b == 0 && c == 0) return n;
    int& sol = dp[n][a][b][c];
    if(sol != -1) return sol;
    sol = INF;
    sol = min(sol, DFS(n + 1, a - 9, b - 3, c - 1));
    sol = min(sol, DFS(n + 1, a - 9, b - 1, c - 3));
    sol = min(sol, DFS(n + 1, a - 1, b - 9, c - 3));
    sol = min(sol, DFS(n + 1, a - 3, b - 9, c - 1));
    sol = min(sol, DFS(n + 1, a - 3, b - 1, c - 9));
    sol = min(sol, DFS(n + 1, a - 1, b - 3, c - 9));
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    memset(dp, -1, sizeof(dp));
    for(int i = 0; i < N; ++i)
        cin >> arr[i];
    cout << DFS(0, arr[0], arr[1], arr[2]);    
    return 0;
}