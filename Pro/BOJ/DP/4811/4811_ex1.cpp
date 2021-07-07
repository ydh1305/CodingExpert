#include <iostream>
#include <cstring>
using namespace std;

int N;
long long dp[60][31][31];

long long DFS(int n, int A, int B) {
    if(n == N * 2) return 1;
    long long& sol = dp[n][A][B];
    if(sol != -1) return sol;
    sol = 0;
    if(A)
        sol = sol + DFS(n + 1, A - 1, B + 1);
    if(B)
        sol = sol + DFS(n + 1, A, B - 1);
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