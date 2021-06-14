#include <iostream>
using namespace std;

#define INF 2501

int N, sol;
int map[50][50];
int dp[50][50][4];
bool visit[50][50];

int hh[4] = { -1, 1, 0, 0 };
int ww[4] = {  0, 0, -1, 1 };

void DFS(int h, int w, int in, int go, int cnt) {
    int H, W;
    for(int out = 0; out < 4; ++out) {
        if(map[h][w] == 1 || map[h][w] == 2)
            if(in != out) continue;
        if(map[h][w] >= 3 && map[h][w] <= 6) {
            if(in == 0 || in == 1)
                if(out != 2 && out != 3) continue;
            if(in == 2 || in == 3)
                if(out != 0 && out != 1) continue;
        }
        H = h + hh[out];
        W = w + ww[out];
        if(!go && H == N - 1 && W == N && sol > cnt) {
            sol = cnt;
            return;
        }
        if(go && H == 0 && W == -1 && sol > cnt) {
            sol = cnt;
            return;
        }
        if(!map[H][W]) continue;
        if(H < 0 || W < 0 || H >= N || W >= N) continue;
        if(visit[H][W]) continue;
        if(dp[H][W][out] > cnt + 1) {      
            dp[H][W][out] = cnt + 1;
            visit[H][W] = true;
            DFS(H, W, out, go, cnt + 1);
            visit[H][W] = false;
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N;
        for(int h = 0; h < N; ++h) {
            for(int w = 0; w < N; ++w) {
                for(int d = 0; d < 4; ++d)
                    dp[h][w][d] = INF;
                cin >> map[h][w];
            }
        }
        sol = INF;
        DFS(0, 0, 3, 0, 1);
        for(int h = 0; h < N; ++h)
            for(int w = 0; w < N; ++w)
                for(int d = 0; d < 4; ++d)
                    dp[h][w][d] = INF;
        DFS(N - 1, N - 1, 2, 1, 1);
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}