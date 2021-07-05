#include <iostream>
#include <cstring>
using namespace std;

struct Pos {
    int h;
    int w;
};
Pos pos[300];

int N, K, nP, sol;
int map[101][101];
bool visit[301];
int S[301];

int find_h(int h, int w) {
    int y = h + 1;
    int cnt = 1;
    while(true) {
        if(!map[y][w]) break;
        y++;
        cnt++;
    }
    return cnt;
}

int find_w(int h, int w) {
    int x = w + 1;
    int cnt = 1;
    while(true) {
        if(!map[h][x]) break;
        x++;
        cnt++;
    }
    return cnt;
}

int DFS(int h, int w) {
    int nH = find_h(h, w);
    int nW = find_w(h, w);
    int xx = min(nH, nW);
    int sum = 0;
    for(int Z = xx; Z >= 1; --Z) {
        sum = 0;
        memset(visit, false, sizeof(visit));
        for(int H = h; H < h + Z; ++H) {
            for(int W = w; W < w + Z; ++W) {
                if(!visit[map[H][W]]) {
                    visit[map[H][W]] = true;
                    sum = sum + S[map[H][W]];
                }
            }
        }
        if(sum == (Z * Z)) return Z;
    }
    return 0;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N >> K;
        memset(map, 0, sizeof(map));
        memset(S, 0, sizeof(S));
        nP = 0;
        for(int i = 1; i <= N; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            for(int y = y1; y < y2; ++y)
                for(int x = x1; x < x2; ++x)
                    map[y][x] = i;
            pos[nP++] = { y1, x1 };
            S[i] = (y2 - y1) * (x2 - x1);
        }
        sol = 0;
        for(int i = 0; i < nP; ++i) {
            int ret = DFS(pos[i].h, pos[i].w);
            if(sol < ret) sol = ret;
        }
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}