#include <bits/stdc++.h>
using namespace std;

struct data {
    int x;
    int y;
    int d;
    int k;
};
data D[1000];
bool visit[1000];

int yy[4] = { 1, -1, 0, 0 };
int xx[4] = { 0, 0, -1, 1 };

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; t++) {
        int N; cin >> N;
        memset(visit, false, sizeof(visit));
        for(int j = 0; j < N; j++) {
            cin >> D[j].x >> D[j].y >> D[j].d >> D[j].k;
            D[j].x = D[j].x * 2;
            D[j].y = D[j].y * 2;
        }
        int Ax, Ay, Bx, By;
        vector<vector<pair<int, int>>> v(4001);
        for(int i = 0; i < N; i++) {
            data A = D[i];
            for(int j = i + 1; j < N; j++) {
                data B = D[j];
                Ax = (B.x - A.x) * xx[A.d];
                Ay = (B.y - A.y) * yy[A.d];
                Bx = (A.x - B.x) * xx[B.d];
                By = (A.y - B.y) * yy[B.d];
                if(A.d == 0 || A.d == 1) {
                    if(A.d + B.d == 1) {
                        if(A.x == B.x)
                            v[Ay >> 1].push_back({i, j});
                    } else {
                        if(Ay > 0 && Ay == Bx)
                            v[Ay].push_back({i, j});
                    }
                }
                else {
                    if(A.d + B.d == 5) {
                        if(A.y == B.y)
                            v[Ax >> 1].push_back({i, j});
                    } else {
                        if(Ax > 0 && Ax == By)
                            v[Ax].push_back({i, j});
                    }
                }
            }
        }
        int sol = 0;
        pair<int, int> n;
        for(int i = 0; i <= 4000; i++) {
            if(v[i].empty()) continue;
            set<int> s;
            for(auto n : v[i]) {
                if(!visit[n.first] && !visit[n.second]) {
                    s.insert(n.first);
                    s.insert(n.second);
                }
            }
            for(auto n : s) {
                visit[n] = true;
                sol = sol + D[n].k;
            }
        }
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}