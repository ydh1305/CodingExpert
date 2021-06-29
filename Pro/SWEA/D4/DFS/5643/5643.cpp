#include <iostream>
#include <cstring>
using namespace std;

int N, M;
int dist[501][501];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N >> M;
        memset(dist, 0, sizeof(dist));
        for(int i = 0; i < M; ++i) {
            int a, b; cin >> a >> b;
            dist[a][b] = 1;
        }
        for(int k = 1; k <= N; ++k) {
            for(int i = 1; i <= N; ++i) {
                for(int j = 1; j <= N; ++j) {
                    if(dist[i][k] == 1 && dist[k][j] == 1)
                        dist[i][j] = 1;
                }
            }
        }
        int sol = 0;
        for(int i = 1; i <= N; ++i) {
            int cnt = 0;
            for(int j = 1; j <= N; ++j) {
                if(i == j) continue;
                if(dist[i][j] || dist[j][i]) cnt++;
            }
            if(cnt == N - 1) sol++;
        }
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}