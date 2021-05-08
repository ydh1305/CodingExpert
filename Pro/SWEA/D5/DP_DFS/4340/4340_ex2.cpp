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

void DFS(int h, int w, int in, int cnt, int dir) {
    int H, W;
    for(int out = 0; out < 4; out++) {
        if(map[h][w] == 1 || map[h][w] == 2)
            if(in != out) continue;
        if(map[h][w] >= 3 && map[h][w] <= 6) {
            if(in == 2 || in == 3)
                if(out != 0 && out != 1) continue;
            if(in == 0 || in == 1)
                if(out != 2 && out != 3) continue;
        }
        H = h + hh[out];
        W = w + ww[out];
        if(dir == 0 && H == N - 1 && W == N && cnt < sol) {
            sol = cnt;
            continue;
        }
        if(dir == 1 && H == 0 && W == -1 && cnt < sol) {
            sol = cnt;
            continue;
        }
        if(H < 0 || W < 0 || H > N - 1 || W > N - 1) continue;
        if(!map[H][W]) continue;
        if(visit[H][W]) continue;
        if(dist[H][W][out] < cnt + 1) continue;
        dist[H][W][out] = cnt + 1;
        visit[H][W] = true;
        DFS(H, W, out, cnt + 1, dir);
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
        for(int h = 0; h < N; h++)
            for(int w = 0; w < N; w++)
                for(int d = 0; d < 4; d++)
                    dist[h][w][d] = INF;
        dist[N - 1][N - 1][2] = 1;
        DFS(N - 1, N - 1, 2, 1, 1);
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}