#include <iostream>
#include <cstring>
using namespace std;

struct data {
    int h;
    int w;
};
data WH[5][2];

int map[102][102];

int hh[4] = { -1, 1, 0, 0 };
int ww[4] = { 0, 0, -1, 1 };
int dir[6][4] = { 
    {0, 0, 0, 0},
    {1, 3, 0, 2},
    {3, 0, 1, 2},
    {2, 0, 3, 1},
    {1, 2, 3, 0},
    {1, 0, 3, 2}
};

int DFS(int h, int w, int d) {
    int S = h, E = w, ret = 0;
    int H = h, W = w;
    while(true) {
        H = H + hh[d];
        W = W + ww[d];
        if((S == H && E == W) || map[H][W] == -1) return ret;
        if(!map[H][W]) continue;
        if(map[H][W] >= 1 && map[H][W] <= 5) {
            d = dir[map[H][W]][d];
            ret = ret + 1;
        }
        else {
            int n = map[H][W] - 6;
            if(WH[n][0].h == H && WH[n][0].w == W)
                H = WH[n][1].h, W = WH[n][1].w;
            else
                H = WH[n][0].h, W = WH[n][0].w;
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        memset(WH, 0, sizeof(WH));
        int N; cin >> N;
        for(int h = 1; h <= N; h++) {
            for(int w = 1; w <= N; w++) {
                cin >> map[h][w];
                if(map[h][w] >= 6) {
                    int n = map[h][w] - 6;
                    int idx = 0;
                    if(WH[n][idx].h) idx = 1;
                    WH[n][idx].h = h, WH[n][idx].w = w;
                }
            }
        }
        for(int j = 0; j <= N + 1; j++)
            map[j][0] = map[j][N + 1] = map[0][j] = map[N + 1][j] = 5;
        int sol = 0;
        for(int h = 1; h <= N; h++) {
            for(int w = 1; w <= N; w++) {
                if(!map[h][w]) {
                    for(int d = 0; d < 4; d++) {
                        int nh = h + hh[d];
                        int nw = w + ww[d];
                        if(!map[nh][nw]) continue;
                        sol = max(sol, DFS(h, w, d));
                    }
                }
            }
        }
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}