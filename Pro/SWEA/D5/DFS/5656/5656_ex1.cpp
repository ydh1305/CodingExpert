#include <iostream>
#include <cstring>
using namespace std;

int N, H, W;
int map[15][12];

int hh[4] = { -1, 1, 0, 0 };
int ww[4] = { 0, 0, -1, 1 };

int find(int w) {
    int h = 0;
    while(h < H) {
        if(map[h][w]) break;
        h++;
    }
    return h;
}

int spread(int h, int w) {
    int cnt = 1;
    int size = map[h][w];
    map[h][w] = 0;
    for(int d = 0; d < 4; d++) {
        int nh = h;
        int nw = w;
        for(int i = 0; i < size; i++) {
            if(nh < 0 || nh >= H || nw < 0 || nw >= W) break;
            if(map[nh][nw])
                cnt = cnt + spread(nh, nw);
            nh = nh + hh[d];
            nw = nw + ww[d];
        }
    }
    return cnt;
}

void update(void) {
    for(int w = 0; w < W; w++) {
        int s = H - 1, e = H - 1;
        while(s >= 0) {
            if(map[s][w]) {
                int temp = map[s][w];
                map[s][w] = 0;
                map[e][w] = temp;
                s--;
                e--;
            }
            else s--;
        }
    }
}

int DFS(int n) {
    if(n == N) return 0;
    int tmp[15][12];
    int sol = 0;
    memcpy(tmp, map, sizeof(map));
    for(int w = 0; w < W; w++) {
        int h = find(w);
        if(h == H) continue;
        int ret = spread(h, w);
        update();
        sol = max(sol, DFS(n + 1) + ret);
        memcpy(map, tmp, sizeof(tmp));
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T; 
    for(int i = 1; i <= T; i++) {
        cin >> N >> W >> H;
        int total = 0;
        for(int h = 0; h < H; h++) {
            for(int w = 0; w < W; w++) {
                cin >> map[h][w];
                if(map[h][w]) total = total + 1;
            }
        }
        cout << '#' << i << ' ' << total - DFS(0) << '\n';
    }
    return 0;
}