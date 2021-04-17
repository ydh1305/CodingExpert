#include <iostream>
using namespace std;

const int MAX=1000001;
int A[MAX];
long long dp[MAX];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int N; cin >> N;
        for(int j = 0; j < N; j++) 
            cin >> A[j];
        dp[0] = A[0];
        dp[1] = max(A[0], A[1]);
        for(int j = 2; j < N; j++)
            dp[j] = max(dp[j - 2] + A[j], dp[j - 1]);
        printf("#%d %lld\n", i, dp[N - 1]);
    }
    return 0;
}