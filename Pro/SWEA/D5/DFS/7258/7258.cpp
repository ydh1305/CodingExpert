#include <bits/stdc++.h>
using namespace std;

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define MAX 20
bool visit[MAX + 1][MAX + 1][16][4];
char arr[MAX + 1][MAX + 1];
int N, M;
bool finish;

int hh[4] = { -1, 1, 0, 0 };
int ww[4] = { 0, 0, -1, 1 };

void DFS(int h, int w, int v, int d) {
    if(h == -1) h = N - 1;
    else if(h == N) h = 0;
    else if(w == -1) w = M - 1;
    else if(w == M) w = 0;
    if(visit[h][w][v][d]) return;
    visit[h][w][v][d] = true;
    if(arr[h][w] == '@') {
        finish = true;
        return;
    }
    else if(arr[h][w] == '<') DFS(h + hh[LEFT], w + ww[LEFT], v, LEFT);
    else if(arr[h][w] == '>') DFS(h + hh[RIGHT], w + ww[RIGHT], v, RIGHT);
    else if(arr[h][w] == '^') DFS(h + hh[UP], w + ww[UP], v, UP);
    else if(arr[h][w] == 'v') DFS(h + hh[DOWN], w + ww[DOWN], v, DOWN);
    else if(arr[h][w] == '_') {
        if(v == 0) DFS(h + hh[RIGHT], w + ww[RIGHT], v, RIGHT);
        else DFS(h + hh[LEFT], w + ww[LEFT], v, LEFT);
    }
    else if(arr[h][w] == '|') {
        if(v == 0) DFS(h + hh[DOWN], w + ww[DOWN], v, DOWN);
        else DFS(h + hh[UP], w + ww[UP], v, UP);
    }
    else if(arr[h][w] == '?') {
        DFS(h + hh[LEFT], w + ww[LEFT], v, LEFT);
        DFS(h + hh[RIGHT], w + ww[RIGHT], v, RIGHT);
        DFS(h + hh[UP], w + ww[UP], v, UP);
        DFS(h + hh[DOWN], w + ww[DOWN], v, DOWN);
    }
    else if(arr[h][w] == '.') DFS(h + hh[d], w + ww[d], v, d);
    else if(arr[h][w] >= '0' && arr[h][w] <= '9') {
        v = arr[h][w] - '0';
        DFS(h + hh[d], w + ww[d], v, d);
    }
    else if(arr[h][w] == '+') {
        if(v == 15) v = 0;
        else v = v + 1;
        DFS(h + hh[d], w + ww[d], v, d);
    }
    else if(arr[h][w] == '-') {
        if(v == 0) v = 15;
        else v = v - 1;
        DFS(h + hh[d], w + ww[d], v, d);
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N >> M;
        memset(visit, false, sizeof(visit));
        for(register int j = 0; j < N; j++)
            cin >> arr[j];
        cout << '#' << i << ' ';
        finish = false;
        DFS(0, 0, 0, RIGHT);
        if(finish) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }
    return 0;
}