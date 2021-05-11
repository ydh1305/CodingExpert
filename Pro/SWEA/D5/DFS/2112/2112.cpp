#include <iostream>
#include <cstring>
using namespace std;

int D, W, K, sol;
int F[13][20];
bool visit[13];

bool check(void) {
    for(int i = 0; i < W; i++) {
        int A = 0, B = 0, pass = 0;
        for(int j = 0; j < D; j++) {
            if(F[j][i] == 0) A++, B = 0;
            else B++, A = 0;
            if(A == K || B == K) pass = 1;
        }
        if(!pass) return false;
    }
    return true;
}

void DFS(int n, int cnt) {
    if(cnt >= sol) return;
    if(check()) {
        sol = min(sol, cnt);
        return;
    }
    for(int i = n; i < D; i++) {
        if(visit[i]) continue;
        visit[i] = true;
        int temp[20] = { 0, };
        memcpy(temp, F[i], sizeof(F[i]));
        for(int j = 0; j < W; j++)
            F[i][j] = 0;
        DFS(i + 1, cnt + 1);
        for(int j = 0; j < W; j++)
            F[i][j] = 1;
        DFS(i + 1, cnt + 1);
        memcpy(F[i], temp, sizeof(F[i]));
        visit[i] = false;
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> D >> W >> K;
        memset(visit, false, sizeof(visit));
        for(int h = 0; h < D; h++)
            for(int w = 0; w < W; w++)
                cin >> F[h][w];
        sol = K;
        DFS(0, 0);
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}