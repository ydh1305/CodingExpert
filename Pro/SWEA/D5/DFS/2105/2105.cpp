#include <iostream>
using namespace std;

#define INF 50
int N, sol;
int map[21][21];
bool visit[101];

int d[4][2] = {
    { -1, 1 },
    { 1, 1 },
    { 1, -1 },
    { -1, -1 }
};

void DFS(int r, int c, int h, int w, int dir, int cnt) {
    if((w + h) * 2 < sol) return;
    if(dir == 3 && w == cnt) {
        if((w + h) * 2 > sol)
            sol = (w + h) * 2;
        return;
    }
    if(visit[map[r][c]]) return;
    visit[map[r][c]] = true;
    if(dir == 0) {
        if(cnt < h) 
            DFS(r + d[dir][0], c + d[dir][1], h, w, dir, cnt + 1);
        else
            DFS(r + d[dir + 1][0], c + d[dir + 1][1], h, w, dir + 1, 1);
    }
    if(dir == 1) {
        if(cnt < w)
            DFS(r + d[dir][0], c + d[dir][1], h, w, dir, cnt + 1);
        else
            DFS(r + d[dir + 1][0], c + d[dir + 1][1], h, w, dir + 1, 1);
    }
    if(dir == 2) {
        if(cnt < h)
            DFS(r + d[dir][0], c + d[dir][1], h, w, dir, cnt + 1);
        else
            DFS(r + d[dir + 1][0], c + d[dir + 1][1], h, w, dir + 1, 1);
    }
    if(dir == 3)
        DFS(r + d[dir][0], c + d[dir][1], h, w, dir, cnt + 1);
    visit[map[r][c]] = false;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N;
        for(int h = 1; h <= N; h++)
            for(int w = 1; w <= N; w++)
                cin >> map[h][w];
        sol = -1;
        for(int r = 2; r < N; r++) {
            for(int c = 1; c < N - 1; c++) {
                for(int h = 1; h < r; h++) {
                    int max_w = INF;
                    if(N - c - h < max_w) max_w = N - c - h;
                    if(N - r < max_w) max_w = N - r;
                    for(int w = 1; w <= max_w; w++)
                        DFS(r, c, h, w, 0, 0);
                }
            }
        }
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}