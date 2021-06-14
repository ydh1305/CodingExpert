#include <iostream>
using namespace std;

int N, sol;
int map[21][21];
bool visit[101];

int hh[4] = { -1, 1, 1, -1 };
int ww[4] = { 1, 1, -1, -1 };

void DFS(int h, int w, int r, int c, int d, int cnt) {
    int tmp = (r + c) * 2;
    if(tmp < sol) return;
    if(d == 3 && c == cnt) {
        if(sol < tmp)
            sol = tmp;
        return;
    }
    if(visit[map[h][w]]) return;
    visit[map[h][w]] = true;
    if(d == 0) {
        if(cnt < r)
            DFS(h + hh[d], w + ww[d], r, c, d, cnt + 1);
        else
            DFS(h + hh[d + 1], w + ww[d + 1], r, c, d + 1, 1);
    }
    else if(d == 1) {
        if(cnt < c)
            DFS(h + hh[d], w + ww[d], r, c, d, cnt + 1);
        else
            DFS(h + hh[d + 1], w + ww[d + 1], r, c, d + 1, 1);
    }
    else if(d == 2) {
        if(cnt < r)
            DFS(h + hh[d], w + ww[d], r, c, d, cnt + 1);
        else
            DFS(h + hh[d + 1], w + ww[d + 1], r, c, d + 1, 1);
    }
    else
        DFS(h + hh[d], w + ww[d], r, c, d, cnt + 1);
    visit[map[h][w]] = false;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N;
        for(int h = 1; h <= N; ++h)
            for(int w = 1; w <= N; ++w)
                cin >> map[h][w];
        sol = -1;
        for(int h = 2; h < N; ++h) {
            for(int w = 1; w < N - 1; ++w) {
                int max_c;
                for(int r = 1; r < h; ++r) {
                    max_c = N - r - w;
                    if(max_c > N - h) max_c = N - h;
                    for(int c = 1; c <= max_c; ++c) {
                        DFS(h, w, r, c, 0, 0);
                    }
                }
            }
        }
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}