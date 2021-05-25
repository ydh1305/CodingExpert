#include <iostream>
using namespace std;

long long dp[1000000];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int N; cin >> N;
        for(register int i = 0; i < N; ++i) {
            long long x; cin >> x;
            if(i == 0) dp[0] = x;
            else if(i == 1) dp[1] = max(dp[0], x);
            else dp[i] = max(dp[i - 2] + x, dp[i - 1]);
        }
        cout << '#' << t << ' ' << dp[N - 1] << '\n';
    }
    return 0;
}