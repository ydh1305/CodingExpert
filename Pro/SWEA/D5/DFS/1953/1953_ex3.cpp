#include <iostream>
using namespace std;

#define INF 2501

int N, M, R, C, L, sol;
int map[50][50];
bool visit[50][50];
int dist[50][50];

int hh[4] = { -1, 1, 0, 0 };
int ww[4] = { 0, 0, -1, 1 };
int dir[4] = { 1, 0, 3, 2 };
int p[8][4] = {
    { 0, 0, 0, 0 },
    { 1, 1, 1, 1 },
    { 1, 1, 0, 0 },
    { 0, 0, 1, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 0, 1 },
    { 0, 1, 1, 0 },
    { 1, 0, 1, 0 }
};

void DFS(int h, int w, int cnt) {
    if(cnt > L) return;
    if(!visit[h][w]) {
        sol++;
        visit[h][w] = true;
    }
    for(int i = 0; i < 4; ++i) {
        int H = h + hh[i];
        int W = w + ww[i];
        if(H < 0 || W < 0 || H >= N || W >= M) continue;
        if(p[map[h][w]][i] == 1 && p[map[H][W]][dir[i]] == 1) {
            if(dist[H][W] > cnt + 1) {
                dist[H][W] = cnt + 1;
                DFS(H, W, cnt + 1);
            }
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N >> M >> R >> C >> L;
        for(int h = 0; h < N; ++h) {
            for(int w = 0; w < M; ++w) {
                cin >> map[h][w];
                dist[h][w] = INF;
                visit[h][w] = false;
            }
        }
        sol = 0;
        DFS(R, C, 1);
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}