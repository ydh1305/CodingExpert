#include <iostream>
#include <algorithm>
using namespace std;

#define INF 1000000

int N, M, sol;
int A[1000], B[1000];
int dp[1000][1000];

int solve(void) {
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= M; ++j) {
            dp[i][j] = dp[i - 1][j - 1] + abs(A[i - 1] - B[j - 1]);
            if(i > j) 
                dp[i][j] = min(dp[i][j], dp[i - 1][j]);
            if(i < j)
                dp[i][j] = min(dp[i][j], dp[i][j - 1]); 
        }
    }
    return dp[N][M];
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for(int i = 0; i < N; ++i)
        cin >> A[i];
    for(int i = 0; i < M; ++i)
        cin >> B[i];
    sort(A, A + N);
    sort(B, B + M);
    cout << solve() << '\n';
    return 0;
}