#include <iostream>
#include <cstring>
using namespace std;

struct data {
    int h;
    int w;
    int n;
    int d;
    int s;
};
struct data D[1001];

int visit[100][100];
int N, M, K;

int hh[5] = { 0, -1, 1, 0, 0 };
int ww[5] = { 0, 0, 0, -1, 1 };
int rev[5] = { 0, 2, 1, 4, 3 };

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N >> M >> K;
        for(int j = 1; j <= K; j++) {
            cin >> D[j].h >> D[j].w >> D[j].n >> D[j].d;
            D[j].s = 0;
        }
        for(int k = 0; k < M; k++) {
            memset(visit, 0, sizeof(visit));
            for(int j = 1; j <= K; j++) {
                if(!D[j].n) continue;
                int H = D[j].h + hh[D[j].d];
                int W = D[j].w + ww[D[j].d];
                if(H == 0 || H == N - 1 || W == 0 || W == N - 1) {
                    D[j].h = H, D[j].w = W;
                    D[j].n = D[j].n / 2;
                    D[j].d = rev[D[j].d];
                    continue;
                }
                int idx = visit[H][W];
                if(idx) {
                    if(D[j].n < D[idx].n) {
                        D[idx].s = D[idx].s + D[j].n + D[j].s;
                        D[j].h = D[j].w = D[j].n = D[j].d = D[j].s = 0;
                    } else {
                        D[j].s = D[j].s + D[idx].n + D[idx].s;
                        D[j].h = H; D[j].w = W;
                        visit[H][W] = j;
                        D[idx].h = D[idx].w = D[idx].n = D[idx].d = D[idx].s = 0;
                    }
                } else {
                    visit[H][W] = j;
                    D[j].h = H, D[j].w = W;
                }
            }
            for(int j = 1; j <= K; j++) {
                if(D[j].s) D[j].n = D[j].n + D[j].s;
                D[j].s = 0;
            }
        }
        int sol = 0;
        for(int j = 1; j <= K; j++) {
            if(!D[j].n) continue;
            sol = sol + D[j].n;
        }
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}