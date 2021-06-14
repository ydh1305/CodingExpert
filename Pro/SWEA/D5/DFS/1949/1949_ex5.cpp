#include <iostream>
using namespace std;

struct Top {
    int h;
    int w;
};
Top top[5];

int N, K, nTop, sol;
int map[8][8];
bool visit[8][8];

int hh[4] = { -1, 1, 0, 0 };
int ww[4] = { 0, 0, -1, 1 };

void DFS(int h, int w, int prev, bool cut, int cnt) {
    if(sol < cnt) sol = cnt;
    visit[h][w] = true;
    for(int i = 0; i < 4; ++i) {
        int H = h + hh[i];
        int W = w + ww[i];
        if(H < 0 || W < 0 || H >= N || W >= N) continue;
        if(visit[H][W]) continue;
        if(cut) {
            if(prev > map[H][W])
                DFS(H, W, map[H][W], cut, cnt + 1);
        } else {
            if(prev > map[H][W])
                DFS(H, W, map[H][W], cut, cnt + 1);
            else if(prev > map[H][W] - K)
                DFS(H, W, map[h][w] - 1, true, cnt + 1);
        }
    }
    visit[h][w] = false;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N >> K;
        int max = 0;
        for(int h = 0; h < N; ++h) {
            for(int w = 0; w < N; ++w) {
                cin >> map[h][w];
                if(max < map[h][w]) {
                    nTop = 0;
                    max = map[h][w];
                    top[nTop++] = { h, w };
                } 
                else if(max == map[h][w])
                    top[nTop++] = { h, w };
            }
        }
        sol = 0;
        for(int i = 0; i < nTop; ++i)
            DFS(top[i].h, top[i].w, map[top[i].h][top[i].w], false, 1);
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}