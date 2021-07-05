#include <iostream>
#include <cstring>
using namespace std;

int N, K, sum, sol;
int map[101][101];
int chk[101][101];
int S[301];
bool visit[301];

int solve(int H, int W, int d) {
    int sum = 0;
    memset(visit, false, sizeof(visit));
    for(int h = H - d; h <= H; ++h) {
        for(int w = W - d; w <= W; ++w) {
            if(!visit[chk[h][w]]) {
                visit[chk[h][w]] = true;
                sum = sum + S[chk[h][w]];
            }
        }
    }
    return sum;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N >> K;
        memset(S, 0, sizeof(S));
        memset(map, 0, sizeof(map));
        memset(chk, 0, sizeof(chk));
        for(int i = 1; i <= N; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            for(int h = y1; h < y2; ++h) {
                for(int w = x1; w < x2; ++w) {
                    map[h][w] = 1; chk[h][w] = i;
                    S[i] = S[i] + 1;
                }
            }
        }
        for(int h = 1; h <= K; ++h) {
            for(int w = 1; w <= K; ++w) {
                if(map[h][w])
                    map[h][w] = min(map[h - 1][w], min(map[h - 1][w - 1], map[h][w - 1])) + 1;
            }
        }
        sol = 0;
        for(int h = 1; h <= K; ++h) {
            for(int w = 1; w <= K; ++w) {  
                if(map[h][w]) {
                    int ret = solve(h, w, map[h][w] - 1);
                    if((map[h][w] * map[h][w]) == ret) {
                        sol = map[h][w];
                    }
                }
            }
        }
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}