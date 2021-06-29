#include <iostream>
#include <cstring>
using namespace std;

#define INF 200001

int N, B, val;
int S[20];
int dp[1 << 20][20];

int DFS(int bit, int n, int sum) {
    if(n == N) {
        if(sum >= B) {
            val = min(sum, val);
        }
        return val - B;
    }
    int& sol = dp[bit][n];
    if(sol != INF) return sol;
    sol = min(sol, DFS(bit | (1 << n), n + 1, sum + S[n]));
    sol = min(sol, DFS(bit, n + 1, sum));
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N >> B;
        for(int i = 0; i < (1 << N); ++i)
            for(int j = 0; j < N; ++j)
                dp[i][j] = INF;
        for(int i = 0; i < N; ++i)
            cin >> S[i];
        val = INF;
        cout << '#' << t << ' ' << DFS(0, 0, 0) << '\n';
    }
    return 0;
}