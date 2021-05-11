#include <bits/stdc++.h>
using namespace std;

struct data {
    int x;
    int y;
    int dir;
    int k;
};
data D[1000];
bool visit[1001];

int yy[4] = { 1, -1, 0, 0 };
int xx[4] = { 0, 0, -1, 1 };

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int N; cin >> N;
        memset(visit, false, sizeof(visit));
        for(int j = 0; j < N; ++j) {
            cin >> D[j].x >> D[j].y >> D[j].dir >> D[j].k;
            D[j].x = D[j].x * 2;
            D[j].y = D[j].y * 2;
        }
        vector<vector<pair<int, int>>> v(4001);
        int Ax, Ay, Bx, By;
        for(int i = 0; i < N; ++i) {
            data A = D[i];
            for(int j = i + 1; j < N; ++j) {
                data B = D[j];
                Ax = (B.x - A.x) * xx[A.dir];
                Ay = (B.y - A.y) * yy[A.dir];
                Bx = (A.x - B.x) * xx[B.dir];
                By = (A.y - B.y) * yy[B.dir];
                if(A.dir == 0 || A.dir == 1) {
                    if(A.dir + B.dir == 1) {
                        if(A.x == B.x) 
                            v[Ay >> 1].push_back({i, j});
                    } 
                    else {
                        if(Ay > 0 && Ay == Bx) 
                            v[Ay].push_back({i, j});
                    }
                }
                else {
                    if(A.dir + B.dir == 5) {
                        if(A.y == B.y)
                            v[Ax >> 1].push_back({i, j});
                    }
                    else {
                        if(Ax > 0 && Ax == By)
                            v[Ax].push_back({i, j});
                    }
                }
            }
        }
        int sol = 0;
        pair<int, int> a;
        for(int i = 0; i <= 4000; i++) {
            if(v[i].empty()) continue;
            set<int> s;
            for(auto a : v[i]) {
                if(!visit[a.first] && !visit[a.second]) {
                    s.insert(a.first);
                    s.insert(a.second);
                }
            }
            for(auto a : s) {
                visit[a] = true;
                sol = sol + D[a].k;
            }
        }
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}