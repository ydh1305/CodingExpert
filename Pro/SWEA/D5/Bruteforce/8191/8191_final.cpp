#include <iostream>
using namespace std;

int dp[200001];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int N; cin >> N;
        for(int i = 0; i < N; ++i) {
            int x; cin >> x;
            dp[x] = i;
        }
        int sol = 1;
        int prev = dp[1];
        for(register int i = 2; i <= N; ++i) {
            if(prev > dp[i]) sol = sol + 1;
            prev = dp[i];
        }
        printf("#%d %d\n", t, sol);
    }
    return 0;
}