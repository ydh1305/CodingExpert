#include <iostream>
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

int M, A, sol, ret;
int pos[2][101];
bool visit[8];

int yy[5] = { 0, -1, 0, 1, 0 };
int xx[5] = { 0, 0, 1, 0, -1 };

bool check(int n, int m) {
    if((abs(user[n].x - bc[m].x) + abs(user[n].y - bc[m].y)) <= bc[m].c) return true;
    return false;
}

void DFS(int n, int sum) {
    if(n == 2) {
        if(ret < sum) ret = sum;
        return;
    }
    for(int i = 0; i < A; ++i) {
        if(visit[i]) continue;
        if(!check(n, i)) continue;
        visit[i] = true;
        DFS(n + 1, sum + bc[i].p);
        visit[i] = false;
    }
    DFS(n + 1, sum);
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
        user[0].x = 1, user[0].y = 1;
        user[1].x = 10, user[1].y = 10;
        sol = 0;
        for(int i = 0; i <= M; ++i) {
            ret = 0;
            for(int j = 0; j < 2; ++j) {
                user[j].x = user[j].x + xx[pos[j][i]]; 
                user[j].y = user[j].y + yy[pos[j][i]]; 
            }
            DFS(0, 0);
            sol = sol + ret;
        }
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}