#include <iostream>
using namespace std;

int map[8][8];
int visit[8];
int hh[4] = { -1, 1, 0, 0 };
int ww[4] = { 0, 0, -1, 1 };
int N, K, sol;

void DFS(int h, int w, bool cut, int prev, int cnt) {
    visit[h] = visit[h] | (1 << w);
    if(sol < cnt) sol = cnt;
    for(int i = 0; i < 4; i++) {
        int nh = h + hh[i];
        int nw = w + ww[i];
        if(nh < 0 || nh >= N || nw < 0 || nw >= N) continue;
        if((visit[nh] & (1 << nw))) continue;
        if(!cut) {
            if(map[h][w] > map[nh][nw])
                DFS(nh, nw, cut, map[nh][nw], cnt + 1);
            else if(map[h][w] > map[nh][nw] - K)
                DFS(nh, nw, true, map[h][w] - 1, cnt + 1);
        }
        else {
            if(prev > map[nh][nw])
                DFS(nh, nw, cut, map[nh][nw], cnt + 1);
        }
    }
    visit[h] = visit[h] & ~(1 << w);
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; t++) {
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
                if(map[h][w] == max) 
                    DFS(h, w, false, 20, 1);
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}