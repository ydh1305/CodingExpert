#include <iostream>
using namespace std;

struct Top {
    int h;
    int w;
};
Top top[5];

int N, K, top_idx, sol;
int map[8][8];
bool visit[8][8];

int hh[4] = { -1, 1, 0, 0 };
int ww[4] = { 0, 0, -1, 1 };

int DFS(int h, int w, int cnt, int prev, bool cut) {
    int H, W;
    visit[h][w] = true;
    if(sol < cnt) sol = cnt;
    for(int i = 0; i < 4; ++i) {
        H = h + hh[i]; W = w + ww[i];
        if(H < 0 || W < 0 || H > N - 1 || W > N - 1) continue;
        if(visit[H][W]) continue;
        if(!cut) {
            if(map[h][w] > map[H][W])
                DFS(H, W, cnt + 1, map[H][W], cut);
            else if(map[h][w] > map[H][W] - K)
                DFS(H, W, cnt + 1, map[h][w] - 1, true);
        }
        else {
            if(prev > map[H][W])
                DFS(H, W, cnt + 1, map[H][W], cut);
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
        int max = 0, top_idx = 0;
        for(int h = 0; h < N; ++h) {
            for(int w = 0; w < N; ++w) {
                cin >> map[h][w];
                if(max < map[h][w]) {
                    max = map[h][w];
                    top_idx = 0;
                    top[top_idx].h = h;
                    top[top_idx++].w = w;
                }
                else if(max == map[h][w]) {
                    top[top_idx].h = h;
                    top[top_idx++].w = w;
                }
            }
        }
        sol = 0;
        for(int i = 0; i < top_idx; ++i)
            DFS(top[i].h, top[i].w, 1, 20, false);
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}