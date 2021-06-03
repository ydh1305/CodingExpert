#include <iostream>
using namespace std;

int arr[1001][1001];
int dp[1001][1001][2];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int N; cin >> N;
        for(int h = 1; h <= N; ++h) {
            for(int w = 1; w <= N; ++w) {
                cin >> arr[h][w];
                int cnt = 0;
                int num = arr[h][w];
                if(num == 0) {
                    dp[h][w][0] = 1000001;
                    dp[h][w][1] = 1000001;
                    continue;
                }
                while(num % 2 == 0) {
                    cnt = cnt + 1;
                    num = num / 2;
                }
                dp[h][w][0] = cnt;
                cnt = 0;
                while(num % 5 == 0) {
                    cnt = cnt + 1;
                    num = num / 5;
                }
                dp[h][w][1] = cnt;
            }
        }
        for(int h = 1; h <= N; ++h) {
            for(int w = 1; w <= N; ++w) {
                if(arr[h][w] == 0) continue;
                if(h == 1 && w == 1) continue;
                if(w == 1) {
                    dp[h][w][0] = dp[h][w][0] + dp[h - 1][w][0];
                    dp[h][w][1] = dp[h][w][1] + dp[h - 1][w][1];
                    continue;
                }
                if(h == 1) {
                    dp[h][w][0] = dp[h][w][0] + dp[h][w - 1][0];
                    dp[h][w][1] = dp[h][w][1] + dp[h][w - 1][1];
                    continue;
                }
                int from_up = min(dp[h][w][0] + dp[h - 1][w][0], dp[h][w][1] + dp[h - 1][w][1]);
                int from_left = min(dp[h][w][0] + dp[h][w - 1][0], dp[h][w][1] + dp[h][w - 1][1]);
                if(from_up < from_left) {
                    dp[h][w][0] = dp[h][w][0] + dp[h - 1][w][0];
                    dp[h][w][1] = dp[h][w][1] + dp[h - 1][w][1];
                }
                else {
                    dp[h][w][0] = dp[h][w][0] + dp[h][w - 1][0];
                    dp[h][w][1] = dp[h][w][1] + dp[h][w - 1][1];
                }
            }
        }
        cout << '#' << t << ' ' << min(dp[N][N][0], dp[N][N][1]) << '\n';
        printf("#%d %d\n", t, min(dp[N][N][0], dp[N][N][1]));
    }
    return 0;
}