#include <iostream>
using namespace std;

int N, M;
int dp[1001][1001];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for(int i = 1; i <= N; ++i) {
        char st[1001];
        cin >> st;
        for(int j = 0; st[j]; ++j)
            dp[i][j + 1] = st[j] - '0';
    }
    int sol = 0;
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= M; ++j) {
            if(dp[i][j])
                dp[i][j] = min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i][j - 1])) + 1;
            if(sol < dp[i][j]) sol = dp[i][j];
        }
    }
    cout << sol * sol << '\n';
    return 0;
}