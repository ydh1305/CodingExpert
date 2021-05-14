#include <bits/stdc++.h>
using namespace std;

struct User {
    int x;
    int y;
};
User user[2];

struct Bc {
    int x;
    int y;
    int c;
    int p;
};
Bc bc[8];

bool visit[8];
int pos[2][101];
int yy[5] = { 0, -1, 0, 1, 0 };
int xx[5] = { 0, 0, 1, 0, -1 };
int M, A, sum;

bool check(int n, int m) {
    if(abs(user[n].x - bc[m].x) + abs(user[n].y - bc[m].y) <= bc[m].c) return true;
    return false;
}

void DFS(int n, int chg) {
    if(n == 2) {
        if(sum < chg) sum = chg;
        return;
    }
    for(int i = 0; i < A; i++) {
        if(visit[i]) continue;
        if(!check(n, i)) continue;
        visit[i] = true;
        DFS(n + 1, bc[i].p + chg);
        visit[i] = false;
    }
    DFS(n + 1, chg);
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> M >> A;
        memset(visit, false, sizeof(visit));
        user[0].x = 1, user[0].y = 1;
        user[1].x = 10, user[1].y = 10;
        for(int j = 0; j < 2; j++)
            for(int k = 1; k <= M; k++)
                cin >> pos[j][k];
        for(int j = 0; j < A; j++)
            cin >> bc[j].x >> bc[j].y >> bc[j].c >> bc[j].p;
        int sol = 0;
        for(int j = 0; j <= M; j++) {
            sum = 0;
            for(int k = 0; k < 2; k++) {
                user[k].x = user[k].x + xx[pos[k][j]];
                user[k].y = user[k].y + yy[pos[k][j]];
            }
            DFS(0, 0);
            sol = sol + sum;
        }
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}