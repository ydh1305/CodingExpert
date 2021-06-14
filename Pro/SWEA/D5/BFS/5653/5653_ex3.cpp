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

int N, M, K;
int wp, rp;
int map[650][650];
int hh[4] = { -1, 1, 0, 0 };
int ww[4] = { 0, 0, -1, 1 };

bool comp(const Queue &a, const Queue &b) {
    return a.k > b.k;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N >> M >> K;
        wp = rp = 0;
        memset(map, false, sizeof(map));
        for(int h = K; h < K + N; ++h) {
            for(int w = K; w < K + M; ++w) {
                cin >> map[h][w];
                if(map[h][w]) 
                    Q[wp++] = { h, w, map[h][w] };
            }
        }
        sort(Q, Q + wp, comp);
        int sol = 0;
        for(int k = K; k >= 1; --k) {
            int size = wp - rp;
            for(int i = 0; i < size; ++i) {
                Queue data = Q[rp++];
                if(data.k-- > 0)
                    Q[wp++] = { data.h, data.w, data.k };
                else {
                    if(map[data.h][data.w] > k) sol = sol + 1;
                    for(int i = 0; i < 4; ++i) {
                        int nh = data.h + hh[i];
                        int nw = data.w + ww[i];
                        if(map[nh][nw]) continue;
                        map[nh][nw] = map[data.h][data.w];
                        Q[wp++] = { nh, nw, map[data.h][data.w] };
                    }
                }
            }
        }
        cout << '#' << t << ' ' << sol + (wp - rp) << '\n';
    }
    return 0;
}