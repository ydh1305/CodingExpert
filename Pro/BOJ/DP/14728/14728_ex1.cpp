#include <iostream>
#include <cstring>
using namespace std;

struct Study {
    int t;
    int s;
};
Study S[100];

int N, T;
int dp[100][10001];

int DFS(int n, int sum) {
    if(n == N) return 0;
    int& sol = dp[n][sum];
    if(sol != -1) return sol;
    sol = 0;
    if(sum + S[n].t <= T)
        sol = max(sol, DFS(n + 1, sum + S[n].t) + S[n].s);
    sol = max(sol, DFS(n + 1, sum));
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> T;
    for(int i = 0; i < N; ++i)
        cin >> S[i].t >> S[i].s;
    memset(dp, -1, sizeof(dp));
    cout << DFS(0, 0) << '\n';
    return 0;
}