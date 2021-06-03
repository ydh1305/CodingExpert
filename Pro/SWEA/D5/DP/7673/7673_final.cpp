#include <bits/stdc++.h>
using namespace std;

#define MAX 1001
int arr[MAX][MAX];
int dp[MAX][MAX][2];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int N; cin >> N;
        int sol = 0;
        for(int h = 1; h <= N; h++) {
            for(int w = 1; w <= N; w++) {
                cin >> arr[h][w];
                if(arr[h][w] == 0) {
                    dp[h][w][0] = 2e9;
                    dp[h][w][1] = 2e9;
                    continue;
                }
                int cnt = 0;
                int num = arr[h][w];
                while(num % 2 == 0) {
                    cnt++;
                    num = num / 2; 
                }
                dp[h][w][0] = cnt;
                cnt = 0;
                while(num % 5 == 0) {
                    cnt++;
                    num = num / 5;
                }
                dp[h][w][1] = cnt;
            }
        }   
        for(int h = 1; h <= N; h++) {
            for(int w = 1; w <= N; w++) {
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
                int from_left = min(dp[h][w][0] + dp[h][w - 1][0], dp[h][w][1] + dp[h][w - 1][1]);
                int from_up = min(dp[h][w][0] + dp[h - 1][w][0], dp[h][w][1] + dp[h - 1][w][1]);
                if(from_up > from_left) {
                    dp[h][w][0] = dp[h][w][0] + dp[h][w - 1][0];
                    dp[h][w][1] = dp[h][w][1] + dp[h][w - 1][1];
                } else {
                    dp[h][w][0] = dp[h][w][0] + dp[h - 1][w][0];
                    dp[h][w][1] = dp[h][w][1] + dp[h - 1][w][1];
                }
            }
        }
        sol = min(dp[N][N][0], dp[N][N][1]);
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}