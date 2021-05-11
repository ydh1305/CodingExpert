#include <iostream>
#include <cstring>
using namespace std;

struct Queue {
    int h;
    int w;
    int t;
};
struct Queue Q[250000];

int map[650][650];
int N, M, K;
int wp, rp;
int hh[4] = { -1, 1, 0, 0 };
int ww[4] = { 0, 0, -1, 1 };

int comp(void const *a, void const *b) {
    struct Queue *m = (struct Queue *)a;
    struct Queue *n = (struct Queue *)b;
    return m->t < n->t;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        memset(map, 0, sizeof(map));
        cin >> N >> M >> K;
        wp = rp = 0;
        int sol = 0;
        for(int h = K; h < K + N; h++) {
            for(int w = K; w < K + M; w++) {
                cin >> map[h][w];
                if(map[h][w]) Q[wp++] = { h, w, map[h][w] };
            }
        }
        qsort(Q, wp, sizeof(struct Queue), comp);
        while(K--) {
            int size = wp - rp;
            for(int n = 0; n < size; n++) {
                struct Queue data = Q[rp++];
                if(data.t-- > 0) 
                    Q[wp++] = { data.h, data.w, data.t };
                else {
                    if(map[data.h][data.w] - 1 > K) sol++;
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