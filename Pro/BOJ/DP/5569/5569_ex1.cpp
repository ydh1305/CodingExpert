#include <iostream>
#include <cstring>
using namespace std;

#define MOD 100000

int W, H;
int dp[101][101][3][3];

int DFS(int h, int w, int Acnt, int Bcnt) {
    if(h > H || w > W) return 0;
    if(h == H && w == W) return 1;
    int& sol = dp[h][w][Acnt][Bcnt];
    if(sol != -1) return sol;
    sol = 0;
    if(Acnt && Bcnt) {
        sol = (sol + DFS(h + 1, w, 2, 0)) % MOD;
        sol = (sol + DFS(h, w + 1, 0, 2)) % MOD;
    }
    else if(Acnt) {
        if(Acnt == 1)
            sol = (sol + DFS(h + 1, w, 2, 0)) % MOD;
        else {
            sol = (sol + DFS(h + 1, w, 2, 0)) % MOD;
            sol = (sol + DFS(h, w + 1, 0, 1)) % MOD;
        }
    }
    else if(Bcnt) {
        if(Bcnt == 1)
            sol = (sol + DFS(h, w + 1, 0, 2)) % MOD;
        else {
            sol = (sol + DFS(h, w + 1, 0, 2)) % MOD;
            sol = (sol + DFS(h + 1, w, 1, 0)) % MOD;
        }
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> W >> H;
    memset(dp, -1, sizeof(dp));
    cout << DFS(1, 1, 1, 1) << '\n';
    return 0;
}