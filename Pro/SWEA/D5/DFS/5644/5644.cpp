#include <iostream>
using namespace std;

struct User {
    int X;
    int Y;
};
struct User user[2];

struct Bc {
    int X;
    int Y;
    int C;
    int P;
    bool V;
};
struct Bc bc[8];

int yy[5] = { 0, -1, 0, 1, 0 };
int xx[5] = { 0, 0, 1, 0, -1 };

int pos[2][101];
int M, A, sol, sum;

bool check(int n, int m) {
    if(abs(user[n].X - bc[m].X) + abs(user[n].Y - bc[m].Y) <= bc[m].C) return true;
    else return false;
}

void DFS(int n, int save) {
    if(n == 2) {
        if(sum < save) sum = save;
        return;
    }
    for(int i = 0; i < A; i++) {
        if(!bc[i].V && check(n, i)) {
            bc[i].V = true;
            DFS(n + 1, save + bc[i].P);
            bc[i].V = false;
        }
    }
    DFS(n + 1, save);
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        user[0].X = 1, user[0].Y = 1;
        user[1].X = 10, user[1].Y = 10;
        cin >> M >> A;
        for(int n = 0; n < 2; n++)
            for(int m = 1; m <= M; m++)
                cin >> pos[n][m];
        for(int n = 0; n < A; n++) {
            cin >> bc[n].X >> bc[n].Y >> bc[n].C >> bc[n].P;
            bc[n].V = false;
        }
        sol = 0;
        for(int m = 0; m <= M; m++) {
            sum = 0;
            for(int n = 0; n < 2; n++) {
                user[n].X = user[n].X + xx[pos[n][m]];
                user[n].Y = user[n].Y + yy[pos[n][m]];
            }
            DFS(0, 0);
            sol = sol + sum;
        }
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}