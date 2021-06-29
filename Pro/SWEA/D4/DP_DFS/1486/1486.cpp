#include <iostream>
#include <cstring>
using namespace std;

#define INF 200001

int N, B, val;
int S[20];
int dp[20][200001];

int DFS(int n, int sum) {
    if(n == N) {
        if(sum >= B) {
            val = min(sum, val);
        }
        return val - B;
    }
    int& sol = dp[n][sum];
    if(sol != -1) return sol;
    sol = INF;
    sol = min(sol, DFS(n + 1, sum + S[n]));
    sol = min(sol, DFS(n + 1, sum));
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N >> B;
        memset(dp, -1, sizeof(dp));
        for(int i = 0; i < N; ++i)
            cin >> S[i];
        val = INF;
        cout << '#' << t << ' ' << DFS(0, 0) << '\n';
    }
    return 0;
}