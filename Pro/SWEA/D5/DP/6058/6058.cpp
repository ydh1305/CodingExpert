#include <bits/stdc++.h>
using namespace std;

int B, L, N;
int offset[16300];
double dp[181][16300];

void make_offset(void) {
    int i = 1;
    int diff = 1, cnt = 0;
    while(i <= 16300) {
        if(cnt == diff) {
            diff++;
            cnt = 0;
        }
        offset[i] = diff;
        cnt++;
        i++;
    }
}

void solve() {
    dp[1][1] = 750 * B;
    for(int i = 1; i < L; i++) {
        for(int j = 1; j <= i * (i + 1) / 2; j++) {
            if(dp[i][j] > 250) {
                double num = dp[i][j] - 250;
                num = num / 3;
                dp[i + 1][j] = dp[i + 1][j] + num;
                dp[i + 1][j + offset[j]] = dp[i + 1][j + offset[j]] + num;
                dp[i + 1][j + offset[j] + 1] = dp[i + 1][j + offset[j] + 1] + num;
            }
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    make_offset();
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> B >> L >> N;
        cout << '#' << i << ' ';
        if(L >= 180) {
            cout << "0\n";
            continue;
        }
        solve();
        if(dp[L][N] > 250) dp[L][N] = 250;
        cout << fixed;
        cout.precision(12);
        cout << dp[L][N] << '\n';
        for(int j = 1; j <= L; j++)
        	for(int k = 1; k <= j * (j + 1) / 2; k++)
            	dp[j][k] = 0;
    }
    return 0;
}