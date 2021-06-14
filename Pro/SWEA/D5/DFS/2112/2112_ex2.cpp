#include <iostream>
#include <cstring>
using namespace std;

int D, W, K, sol;
bool map[13][20];
bool visit[13];

bool check(void) {
    for(int w = 0; w < W; ++w) {
        int A = 0, B = 0, flag = 0;
        for(int h = 0; h < D; ++h) {
            if(map[h][w]) A++, B = 0;
            else B++, A = 0;
            if(A == K || B == K) {
                flag = 1;
                break;
            }
        }
        if(!flag) return false;
    }
    return true;
}

void DFS(int n, int cnt) {
    if(cnt >= K) return;
    if(check()) {
        if(sol > cnt) sol = cnt;
        return;
    }
    for(int i = n; i < D; ++i) {
        if(visit[i]) continue;
        visit[i] = true;
        bool tmp[20];
        memcpy(tmp, map[i], sizeof(bool) * W);
        for(int j = 0; j < W; ++j)
            map[i][j] = 0;
        DFS(i + 1, cnt + 1);
        for(int j = 0; j < W; ++j)
            map[i][j] = 1;
        DFS(i + 1, cnt + 1);
        memcpy(map[i], tmp, sizeof(bool) * W);
        visit[i] = false;
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> D >> W >> K;
        for(int h = 0; h < D; ++h)
            for(int w = 0; w < W; ++w)
                cin >> map[h][w];
        sol = K;
        DFS(0, 0);
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}