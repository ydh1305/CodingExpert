#include <iostream>
using namespace std;

int H, W, sol;
bool map[10][25];
int dp[1 << 10][24];

bool check(int h, int w) {
    if(h >= H - 1 || w >= W - 1) return false;
    if(map[h][w] || map[h + 1][w] || map[h][w + 1] || map[h + 1][w + 1]) return false;
    return true;
}

void DFS(int h, int w, int cnt) {
    if(h >= H - 1) {
        h = 0;
        w++;
    }
    if(w == W - 1) {
        if(sol < cnt) sol = cnt;
        return;
    }
    if(h == 0) {
        int bit = 0;
        for(int i = 0; i < H; i++)
            bit = bit | (map[i][w] << i);
        if(dp[bit][w] >= cnt) return;
        dp[bit][w] = cnt;
    }
    if(check(h, w)) {
        map[h][w] = map[h + 1][w] = map[h][w + 1] = map[h + 1][w + 1] = true;
        DFS(h + 2, w, cnt + 1);
        map[h][w] = map[h + 1][w] = map[h][w + 1] = map[h + 1][w + 1] = false;
    }
    DFS(h + 1, w, cnt);
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> H >> W;
        for(int h = 0; h < H; ++h)
            for(int w = 0; w < W; ++w)
                cin >> map[h][w];
        for(int i = 0; i < (1 << H); ++i)
            for(int j = 0; j < W; ++j)
                dp[i][j] = -1;
        sol = 0;
        DFS(0, 0, 0);
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}