#include <iostream>
#include <cstring>
using namespace std;

int N;
long long dp[61][31][31];

long long DFS(int n, int w, int h) {
    if(n == N * 2) return 1;
    long long& sol = dp[n][w][h];
    if(sol != -1) return sol;
    sol = 0;
    if(w)
        sol = sol + DFS(n + 1, w - 1, h + 1);
    if(h)
        sol = sol + DFS(n + 1, w, h - 1);
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    while(true) {
        cin >> N;
        if(!N) break;
        memset(dp, -1, sizeof(dp));
        cout << DFS(0, N, 0) << '\n';
    }
    return 0;
}