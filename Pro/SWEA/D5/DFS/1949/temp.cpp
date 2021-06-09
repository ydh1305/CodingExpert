#include <iostream>
#include <vector>
using namespace std;

int N, K, sol;
int map[8][8];
int visit[8];
vector<pair<int, int>> v;

int hh[4] = { -1, 1, 0, 0 };
int ww[4] = { 0, 0, -1, 1 };

int DFS(int h, int w, int cnt, int prev, bool cut) {
    visit[h] = visit[h] | (1 << w);
    if(sol < cnt) sol = cnt;
    for(int i = 0; i < 4; ++i) {
        int H = h + hh[i]; 
        int W = w + ww[i];
        if(H < 0 || W < 0 || H > N - 1 || W > N - 1) continue;
        if(visit[H] & (1 << W)) continue;
        if(!cut) {
            if(map[h][w] > map[H][W])
                DFS(H, W, cnt + 1, map[H][W], cut);
            else if(map[h][w] > map[H][W] - K)
                DFS(H, W, cnt + 1, map[h][w] - 1, true);
        }
        else {
            if(prev > map[H][W])
                DFS(H, W, cnt + 1, map[H][W], cut);
        }        
    }
    visit[h] = visit[h] & ~(1 << w);
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N >> K;
        int max = 0;
        for(int h = 0; h < N; ++h) {
            for(int w = 0; w < N; ++w) {
                cin >> map[h][w];
                if(max < map[h][w]) {
                    max = map[h][w];
                    v.clear();
                    v.push_back({h, w});
                }
                else if(max == map[h][w])
                    v.push_back({h, w});
            }
        }
        sol = 0;
        for(int i = 0; i < v.size(); ++i)
            DFS(v[i].first, v[i].second, 1, 20, false);
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}