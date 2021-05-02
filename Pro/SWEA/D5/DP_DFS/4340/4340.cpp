#include <iostream>
using namespace std;

#define MAX 50
#define INF 2501

int N, sol;
int map[MAX][MAX];
int dist[MAX][MAX][4];
bool visit[MAX][MAX];

int hh[4] = { -1, 1, 0, 0 };
int ww[4] = { 0, 0, -1, 1 };

void DFS(int h, int w, int prev, int len, int type) {
    int H, W;
    for(int i = 0; i < 4; i++) {
        if(map[h][w] == 1 || map[h][w] == 2)
            if(prev != i) continue;
        if(map[h][w] >= 3 && map[h][w] <= 6) {
            if(prev == 2 || prev == 3)
                if(i != 0 && i != 1) continue;
            if(prev == 0 || prev == 1)
                if(i != 2 && i != 3) continue;
        }
        H = h + hh[i]; W = w + ww[i];
        if(type == 0 && H == N - 1 && W == N && sol > len) {
            sol = len;
            continue;
        }
        if(type == 1 && H == 0 && W == -1 && sol > len) { 
            sol = len;
            continue;
        }
        if(H < 0 || H >= N || W < 0 || W >= N || !map[H][W] || visit[H][W]) continue;
        if(dist[H][W][i] < len + 1) continue;
        dist[H][W][i] = len + 1;
        visit[H][W] = true;
        DFS(H, W, i, len + 1, type);
        visit[H][W] = false;
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N;
        for(int h = 0; h < N; h++) {
            for(int w = 0; w < N; w++) {
                for(int d = 0; d < 4; d++)
                    dist[h][w][d] = INF;
                cin >> map[h][w];
            }
        }
        sol = INF;
        dist[0][0][3] = 1;
        DFS(0, 0, 3, 1, 0);
        for(int h = 0; h < N; h++) {
            for(int w = 0; w < N; w++) {
                for(int d = 0; d < 4; d++)
                    dist[h][w][d] = INF;
            }
        }
        dist[N - 1][N - 1][2] = 1;
        DFS(N - 1, N - 1, 2, 1, 1);
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}