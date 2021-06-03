#include <iostream>
#include <cstring>
using namespace std;

#define U 0
#define D 1
#define L 2
#define R 3 

int H, W;
int sol;
char map[21][21];
bool dp[21][21][16][4];

int hh[4] = { -1, 1, 0, 0 };
int ww[4] = { 0, 0, -1, 1 };

void DFS(int h, int w, int v, int d) {
    if(h == H) h = 0;
    if(w == W) w = 0;
    if(h == -1) h = H - 1;
    if(w == -1) w = W - 1;
    if(dp[h][w][v][d]) return;
    dp[h][w][v][d] = true;
    if(map[h][w] == '@') {
        sol = 1;
        return;
    }
    else if(map[h][w] == '<') DFS(h + hh[L], w + ww[L], v, L);
    else if(map[h][w] == '>') DFS(h + hh[R], w + ww[R], v, R);
    else if(map[h][w] == '^') DFS(h + hh[U], w + ww[U], v, U);
    else if(map[h][w] == 'v') DFS(h + hh[D], w + ww[D], v, D);
    else if(map[h][w] == '_') {
        if(v == 0) DFS(h + hh[R], w + ww[R], v, R);
        else DFS(h + hh[L], w + ww[L], v, L);
    }
    else if(map[h][w] == '|') {
        if(v == 0) DFS(h + hh[D], w + ww[D], v, D);
        else DFS(h + hh[U], w + ww[U], v, U);
    }
    else if(map[h][w] == '?') {
        DFS(h + hh[L], w + ww[L], v, L);
        DFS(h + hh[R], w + ww[R], v, R);
        DFS(h + hh[U], w + ww[U], v, U);
        DFS(h + hh[D], w + ww[D], v, D);
    }
    else if(map[h][w] == '.') DFS(h + hh[d], w + ww[d], v, d);
    else if(map[h][w] >= '0' && map[h][w] <= '9') DFS(h + hh[d], w + ww[d], map[h][w] - '0', d);
    else if(map[h][w] == '+') {
        if(v == 15) v = 0;
        else v = v + 1;
        DFS(h + hh[d], w + ww[d], v, d);
    }
    else if(map[h][w] == '-') {
        if(v == 0) v = 15;
        else v = v - 1;
        DFS(h + hh[d], w + ww[d], v, d);
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> H >> W;
        memset(dp, false, sizeof(dp));
        for(register int h = 0; h < H; ++h)
            cin >> map[h];
        sol = 0;
        DFS(0, 0, 0, R);
        printf("#%d ", t);
        if(sol)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}