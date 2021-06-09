#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

struct Queue {
    int h;
    int w;
    int k;
};
Queue queue[250000];

int N, M, K;
int wp, rp;
int hh[4] = { -1, 1, 0, 0 };
int ww[4] = { 0, 0, -1, 1 };
int map[650][650];

int comp(const Queue &a, const Queue &b) {
    return a.k > b.k;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N >> M >> K;
        wp = rp = 0;
        memset(map, 0, sizeof(map));
        for(int h = K; h < K + N; ++h) {
            for(int w = K; w < K + M; ++w) {
                cin >> map[h][w];
                if(map[h][w]) 
                    queue[wp++] = { h, w, map[h][w] };
            }
        }
        sort(queue, queue + wp, comp);
        int sol = 0;
        for(int k = K; k >= 1; --k) {
            int size = wp - rp;
            for(int i = 0; i < size; ++i) {
                Queue data = queue[rp++];
                if(data.k-- > 0)
                    queue[wp++] = { data.h, data.w, data.k };
                else {
                    if(map[data.h][data.w] > k) sol = sol + 1;
                    for(int d = 0; d < 4; ++d) {
                        int nh = data.h + hh[d];
                        int nw = data.w + ww[d];
                        if(map[nh][nw]) continue;
                        map[nh][nw] = map[data.h][data.w];
                        queue[wp++] = { nh, nw, map[nh][nw] };
                    }
                }
            }
        }
        cout << '#' << t << ' ' << sol + (wp - rp) << '\n';
    }
    return 0;
}