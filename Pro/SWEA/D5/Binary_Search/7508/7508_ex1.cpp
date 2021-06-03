#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int arr[50], dp[50];

int lower_bound(int s, int e, int v) {
    while(s < e) {
        int m = (s + e) / 2;
        if(arr[m] < v) s = m + 1;
        else e = m;
    }
    return e;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int N; cin >> N;
        for(int i = 0; i < N; ++i)
            cin >> arr[i];
        sort(arr, arr + N);
        int M; cin >> M;
        bool flag = 0;
        memset(dp, 0, sizeof(dp));
        for(int i = 0; i < M; ++i) {
            int x; cin >> x;
            if(arr[N - 1] < x) {
                flag = true;
                break;
            }
            dp[lower_bound(0, N - 1, x)]++;
        }
        cout << '#' << t << ' ';
        if(flag) {
            cout << -1 << '\n';
        } else {
            int sol = 0, r;
            for(int i = 0; i < N; ++i) {
                if(M % (N - i)) r = 1;
                else r = 0;
                int num = min(dp[i], M / (N - i) + r);
                M = M - num;
                dp[i] = dp[i] - num;
                dp[i + 1] = dp[i + 1] + dp[i];
                sol = max(sol, num);
            }
            sol = max(sol, M);
            cout << sol << '\n';
        }
    }
    return 0;
}