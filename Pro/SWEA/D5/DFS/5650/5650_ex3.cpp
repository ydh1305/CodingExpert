#include <iostream>
using namespace std;

struct Wh {
    int h;
    int w;
};
Wh wh[5][2];

int N, sol;
int map[102][102];

int hh[4] = { -1, 1, 0, 0 };
int ww[4] = { 0, 0, -1, 1 };
int dir[6][4] = {
    { 0, 0, 0, 0 },
    { 1, 3, 0, 2 },
    { 3, 0, 1, 2 },
    { 2, 0, 3, 1 },
    { 1, 2, 3, 0 },
    { 1, 0, 3, 2 }
};

int DFS(int h, int w, int d) {
    int S = h, E = w, ret = 0;
    while(true) {
        h = h + hh[d];
        w = w + ww[d];
        if((S == h && E == w) || (map[h][w] == -1)) return ret;
        if(!map[h][w]) continue;
        if(map[h][w] >= 1 && map[h][w] <= 5) {
            d = dir[map[h][w]][d];
            ret++;
        }
        else {
            int idx = map[h][w] - 6;
            if(wh[idx][0].h == h && wh[idx][0].w == w)
                h = wh[idx][1].h, w = wh[idx][1].w;
            else 
                h = wh[idx][0].h, w = wh[idx][0].w;
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N;
        for(int i = 0; i < 5; ++i)
            wh[i][0].h = wh[i][0].w = wh[i][1].h = wh[i][1].w = 0;
        for(int h = 1; h <= N; ++h) {
            for(int w = 1; w <= N; ++w) {
                cin >> map[h][w];
                if(map[h][w] >= 6) {
                    int idx = map[h][w] - 6;
                    int n = 0;
                    if(wh[idx][n].h) n = 1;
                    wh[idx][n].h = h, wh[idx][n].w = w;
                }
            }
        }
        for(int i = 0; i <= N + 1; ++i)
            map[i][0] = map[i][N + 1] = map[0][i] = map[N + 1][i] = 5;
        sol = 0;
        for(int h = 1; h <= N; ++h) {
            for(int w = 1; w <= N; ++w) {
                if(!map[h][w]) {
                    for(int d = 0; d < 4; ++d) {
                        int nh = h + hh[d];
                        int nw = w + ww[d];
                        if(!map[nh][nw]) continue;
                        sol = max(sol, DFS(h, w, d));
                    }
                }
            }
        }
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}