#include <bits/stdc++.h>
using namespace std;

#define INF 987654321

int dist[1001][1001];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int N; cin >> N;
        for(int i = 1; i <= N; ++i)
            for(int j = 1; j <= N; ++j)
                dist[i][j] = INF;
        for(int i = 0; i < N - 1; ++i) {
            int x, y, d; cin >> x >> y >> d;
            dist[x][y] = dist[y][x] = d;
        }
        for(int k = 1; k <= N; ++k) {
            for(int i = 1; i <= N; ++i) {
                for(int j = 1; j <= N; ++j) {
                    if(i == k || k == j || i == j) continue;
                    if(dist[i][k] > 0 && dist[k][j] > 0) {
                        if(dist[i][j] > dist[i][k] + dist[k][j])
                            dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
        long long sol = 0;
        for(int i = 1; i < N; ++i) {
            for(int j = i + 1; j <= N; ++j) {
                sol = sol + dist[i][j];
            }
        }
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}