#include <iostream>
#include <cstring>
using namespace std;

#define INF 987654321

int N, M;
int dp[101][101];
bool V[101];

int DFS(int n, int coupon) {
    if(n > N) return 0;
    int& sol = dp[n][coupon];
    if(sol != -1) return sol;
    sol = INF;
    if(V[n]) sol = min(sol, DFS(n + 1, coupon));
    sol = min(sol, DFS(n + 1, coupon) + 10000);
    sol = min(sol, DFS(n + 3, coupon + 1) + 25000);
    sol = min(sol, DFS(n + 5, coupon + 2) + 37000);
    if(coupon >= 3)
        sol = min(sol, DFS(n + 1, coupon - 3));
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    memset(dp, -1, sizeof(dp));
    for(int i = 0; i < M; ++i) {
        int x; cin >> x;
        V[x] = true;
    }
    cout << DFS(1, 0) << '\n';
    return 0;
}