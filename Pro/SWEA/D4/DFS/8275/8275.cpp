#include <iostream>
using namespace std;

struct Data {
    int s;
    int e;
    int d;
};
Data D[11];

int N, X, M;
int sol;
int arr[7], ans[7], dp[11];

void DFS(int n, int sum) {
    if(n == N + 1) {
        for(int i = 0; i < M; ++i)
            if(dp[D[i].e] - dp[D[i].s - 1] != D[i].d) return;
        if(sol < sum) {
            sol = sum;
            for(int i = 1; i <= N; i++)
                ans[i] = arr[i];
        }
        return;
    }
    for(int i = 0; i <= X; ++i) {
        arr[n] = i;
        dp[n] = dp[n - 1] + i;
        DFS(n + 1, sum + i);
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N >> X >> M;
        for(int i = 0; i < M; ++i)
            cin >> D[i].s >> D[i].e >> D[i].d;
        sol = -1;
        DFS(1, 0);
        cout << '#' << t << ' ';
        if(sol == -1)
            cout << -1 << '\n';
        else {
            for(int i = 1; i <= N; i++)
                cout << ans[i] << ' ';
            cout << '\n';
        }
    }
    return 0;
}