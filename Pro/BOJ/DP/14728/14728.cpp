#include <iostream>
#include <cstring>
using namespace std;

struct Data {
    int t;
    int s;
};
Data D[100];

int N, T;
int dp[100][10001];

int DFS(int n, int sum) {
    if(n == N) return 0;
    int&sol = dp[n][sum];
    if(sol != -1) return sol;
    sol = 0;
    if(sum + D[n].t <= T)
        sol = max(sol, DFS(n + 1, sum + D[n].t) + D[n].s);
    sol = max(sol, DFS(n + 1, sum));
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> T;
    memset(dp, -1, sizeof(dp));
    for(int i = 0; i < N; ++i)
        cin >> D[i].t >> D[i].s;
    cout << DFS(0, 0) << '\n';
    return 0;
}