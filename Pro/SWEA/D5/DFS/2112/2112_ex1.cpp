#include <iostream>
#include <cstring>
using namespace std;

int D, W, K, sol;
int map[13][20];
bool visit[13];

bool check(void) {
    for(int i = 0; i < W; ++i) {
        int nA = 0, nB = 0;
        bool flag = false;
        for(int j = 0; j < D; ++j) {
            if(map[j][i] == 0) nA++, nB = 0;
            else nB++, nA = 0;
            if(nA == K || nB == K) {
                flag = true;
                break;
            } 
        }
        if(flag) continue;
        else return false;
    }
    return true;
}

void DFS(int n, int cnt) {
    if(sol <= cnt) return;
    if(check()) {
        if(sol > cnt) sol = cnt;
        return;
    }
    for(int i = n; i < D; ++i) {
        if(visit[i]) continue;
        visit[i] = true;
        int temp[20];
        memcpy(temp, map[i], sizeof(int) * W);
        for(int j = 0; j < W; ++j)
            map[i][j] = 0;
        DFS(i + 1, cnt + 1);
        for(int j = 0; j < W; ++j)
            map[i][j] = 1;
        DFS(i + 1, cnt + 1);
        memcpy(map[i], temp, sizeof(int) * W);
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