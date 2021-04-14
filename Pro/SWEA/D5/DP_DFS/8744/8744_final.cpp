#include <bits/stdc++.h>
using namespace std;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int N, M; cin >> N >> M;
        int *cnt = new int[N];
        for(int j = 1; j <= N; j++) cnt[j] = N - 1;
        for(int j = 0; j < M; j++) {
            int a, b; cin >> a >> b;
            cnt[a]--; cnt[b]--;
        }
        int sol = INT_MAX;
        for(int j = 1; j <= N; j++)
            sol = min(sol, cnt[j]);
        cout << '#' << i << ' ' << sol - 1 << '\n';
    }
    return 0;
}