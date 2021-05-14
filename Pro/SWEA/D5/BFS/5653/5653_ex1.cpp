#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

struct Queue {
    int h;
    int w;
    int k;
};
Queue Q[250000];

int map[650][650];
int wp, rp;
int hh[4] = { -1, 1, 0, 0 };
int ww[4] = { 0, 0, -1, 1 };

bool comp(const Queue &a, const Queue &b) {
    return a.k > b.k;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int N, M, K; cin >> N >> M >> K;
        memset(map, 0, sizeof(map));
        wp = rp = 0;
        int sol = 0;
        for(int h = K; h < K + N; h++) {
            for(int w = K; w < K + M; w++) {
                cin >> map[h][w];
                if(map[h][w]) Q[wp++] = { h, w, map[h][w] };
            }
        }
        sort(Q, Q + wp, comp);
        for(int k = K - 1; k >= 0; k--) {
            int size = wp - rp;
            for(int j = 0; j < size; j++) {
                Queue data = Q[rp++];
                if(data.k-- > 0)
                    Q[wp++] = { data.h, data.w, data.k };
                else {
                    if(map[data.h][data.w] - 1 > k) sol = sol + 1;
                    for(int d = 0; d < 4; d++) {
                        int nh = data.h + hh[d];
                        int nw = data.w + ww[d];
                        if(map[nh][nw]) continue;
                        map[nh][nw] = map[data.h][data.w];
                        Q[wp++] = { nh, nw, map[nh][nw] };
                    }
                }
            }
        }
        cout << '#' << i << ' ' << sol + (wp - rp) << '\n';
    }
    return 0;
}