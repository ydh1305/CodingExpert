#include <iostream>
#include <cstring>
using namespace std;

struct data {
    int h;
    int w;
};
struct data WH[5][2];

int dir[6][4] = {
    { 0, 0, 0, 0 },
    { 1, 3, 0, 2 },
    { 3, 0, 1, 2 },
    { 2, 0, 3, 1 },
    { 1, 2, 3, 0 },
    { 1, 0, 3, 2 }
};
int hh[4] = { -1, 1, 0, 0 };
int ww[4] = { 0, 0, -1, 1 };

int map[102][102];
int N, sol;

int DFS(int h, int w, int d) {
    int S = h, W = w, ret = 0;
    int dh = h, dw = w;
    while(true) {
        dh = dh + hh[d];
        dw = dw + ww[d];
        if((S == dh && W == dw) || map[dh][dw] == -1) return ret;
        if(!map[dh][dw]) continue;
        if(map[dh][dw] >= 1 && map[dh][dw] <= 5) {
            d = dir[map[dh][dw]][d];
            ret++;
        }
        else {
            int num = map[dh][dw] - 6;
            if(dh == WH[num][0].h && dw == WH[num][0].w)
                dh = WH[num][1].h, dw = WH[num][1].w;
            else
                dh = WH[num][0].h, dw = WH[num][0].w;
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N;
        sol = 0;
        memset(WH, 0, sizeof(WH));
        for(int h = 1; h <= N; h++) {
            for(int w = 1; w <= N; w++) {
                cin >> map[h][w];
                if(map[h][w] >= 6) {
                    int num = map[h][w] - 6;
                    int idx = 0;
                    if(WH[num][idx].h) idx = 1;
                    WH[num][idx].h = h;
                    WH[num][idx].w = w;
                }
            }
        }
        for(int j = 0; j <= N + 1; j++)
            map[0][j] = map[N + 1][j] = map[j][0] = map[j][N + 1] = 5;
        for(int h = 1; h <= N; h++) {
            for(int w = 1; w <= N; w++) {
                if(map[h][w]) continue;
                for(int j = 0; j < 4; j++) {
                    int dh = h + hh[j];
                    int dw = w + ww[j];
                    if(map[dh][dw] == 0) continue;
                    int sum = DFS(h, w, j);
                    if(sol < sum) sol = sum;
                }
            }
        }
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}