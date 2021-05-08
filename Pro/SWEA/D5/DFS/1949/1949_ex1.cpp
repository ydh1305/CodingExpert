#include <iostream>
using namespace std;

int map[8][8];
int visit[8];
int N, K, sol;

int hh[4] = { -1, 1, 0, 0 };
int ww[4] = { 0, 0, -1, 1 };

void DFS(int h, int w, bool cut, int prev, int cnt) {
    visit[h] = visit[h] | (1 << w);
    if(sol < cnt) sol = cnt;
    for(int i = 0; i < 4; i++) {
        int H = h + hh[i];
        int W = w + ww[i];
        if(H < 0 || W < 0 || H > N - 1 || W > N - 1) continue;
        if(!cut) {
            if(map[h][w] > map[H][W] && !(visit[H] & (1 << W)))
                DFS(H, W, cut, map[H][W], cnt + 1);
            else {
                if(map[h][w] > map[H][W] - K && !(visit[H] & (1 << W)))
                    DFS(H, W, true, map[h][w] - 1, cnt + 1);
            }
        }
        else {
            if(prev > map[H][W] && !(visit[H] & (1 << W)))
                DFS(H, W, cut, map[H][W], cnt + 1);
        }
    }
    visit[h] = visit[h] & ~(1 << w);
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N >> K;
        int max = 0;
        for(int h = 0; h < N; h++) {
            for(int w = 0; w < N; w++) {
                cin >> map[h][w];
                if(max < map[h][w]) max = map[h][w];
            }
        }
        sol = 0;
        for(int h = 0; h < N; h++)
            for(int w = 0; w < N; w++)
                if(map[h][w] == max) DFS(h, w, false, 20, 1);
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}