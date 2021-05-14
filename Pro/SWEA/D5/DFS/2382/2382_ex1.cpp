#include <iostream>
#include <cstring>
using namespace std;

struct Data {
    int h;
    int w;
    int c;
    int d;
    int s;
};
Data D[1001];

int hh[5] = { 0, -1, 1, 0, 0 };
int ww[5] = { 0, 0, 0, -1, 1 };
int dir[5] = { 0, 2, 1, 4, 3 };
int visit[100][100];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int N, M, K; cin >> N >> M >> K;
        
        for(int i = 1; i <= K; ++i) {
            cin >> D[i].h >> D[i].w >> D[i].c >> D[i].d;
            D[i].s = 0;
        }
        while(M--) {
            memset(visit, 0, sizeof(visit));
            for(int i = 1; i <= K; ++i) {
                if(!D[i].c) continue;
                int h = D[i].h + hh[D[i].d];
                int w = D[i].w + ww[D[i].d];
                if(h == 0 || w == 0 || h == N - 1 || w == N - 1) {
                    D[i].h = h, D[i].w = w;
                    D[i].c = D[i].c / 2;
                    D[i].d = dir[D[i].d];
                    continue;
                }
                int idx = visit[h][w];
                if(idx) {
                    if(D[idx].c > D[i].c) {
                        D[idx].s = D[idx].s + D[i].c + D[i].s;
                        D[i].h = D[i].w = D[i].c = D[i].d = D[i].s = 0;
                    } else {
                        D[i].s = D[i].s + D[idx].c + D[idx].s;
                        D[i].h = h; D[i].w = w;
                        visit[h][w] = i;
                        D[idx].h = D[idx].w = D[idx].s = D[idx].d = D[idx].c = 0;
                    }
                }
                else {
                    visit[h][w] = i;
                    D[i].h = h; D[i].w = w;
                }
            }
            for(int i = 1; i <= K; ++i) {
                if(D[i].s) D[i].c = D[i].c + D[i].s;
                D[i].s = 0;
            }
        }
        int sol = 0;
        for(int i = 1; i <= K; ++i)
            sol = sol + D[i].c;
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}