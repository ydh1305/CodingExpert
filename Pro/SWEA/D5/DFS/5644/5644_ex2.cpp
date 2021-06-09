#include <iostream>
using namespace std;

struct People {
    int x;
    int y;
};
People P[2];

struct Bc {
    int x;
    int y;
    int c;
    int p;
};
Bc bc[8];

int M, A, sum;
int pos[2][101];
bool visit[8];

int yy[5] = { 0, -1, 0, 1, 0 };
int xx[5] = { 0, 0, 1, 0, -1 };

bool check(int n, int m) {
    int dist = abs(P[n].x - bc[m].x) + abs(P[n].y - bc[m].y);
    if(dist <= bc[m].c) return true;
    return false;
}

void DFS(int n, int chg) {
    if(n == 2) {
        if(sum < chg) sum = chg;
        return;
    }
    for(int i = 0; i < A; ++i) {
        if(visit[i]) continue;
        if(!check(n, i)) continue;
        visit[i] = true;
        DFS(n + 1, chg + bc[i].p);
        visit[i] = false;
    }
    DFS(n + 1, chg);
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> M >> A;
        for(int i = 0; i < 2; ++i)
            for(int j = 1; j <= M; ++j)
                cin >> pos[i][j];
        for(int i = 0; i < A; ++i)
            cin >> bc[i].x >> bc[i].y >> bc[i].c >> bc[i].p;
        P[0].x = 1; P[0].y = 1; P[1].x = 10; P[1].y = 10;
        int sol = 0;
        for(int i = 0; i <= M; ++i) {
            sum = 0;
            for(int j = 0; j < 2; ++j) {
                P[j].x = P[j].x + xx[pos[j][i]];
                P[j].y = P[j].y + yy[pos[j][i]]; 
            }
            DFS(0, 0);
            sol = sol + sum;
        }
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}