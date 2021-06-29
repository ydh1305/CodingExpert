#include <iostream>
#include <cstring>
using namespace std;

struct Subject {
    int p;
    int t;
};
Subject S[1000];
int N, K;
int dp[1000][10001];

int DFS(int n, int sum) {
    if(n == K) return 0;
    int& sol = dp[n][sum];
    if(sol != -1) return sol;
    sol = 0;
    if(sum + S[n].t <= N)
        sol = max(sol, DFS(n + 1, sum + S[n].t) + S[n].p);
    sol = max(sol, DFS(n + 1, sum));
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> K;
    memset(dp, -1, sizeof(dp));
    for(int i = 0; i < K; ++i)
        cin >> S[i].p >> S[i].t;
    cout << DFS(0, 0) << '\n';
    return 0;
}