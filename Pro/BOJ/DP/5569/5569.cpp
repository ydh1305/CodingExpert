#include <iostream>
#include <cstring>
using namespace std;

#define MOD 100000
#define UP 1
#define LEFT 2
#define ALL 3

int W, H;
int dp[105][105][3][3];

int DFS(int h, int w, int a, int b, int stat) {    
    if(h > H || w > W) return 0;
    if(h == H && w == W) return 1;
    int& sol = dp[h][w][a][b];
    if(sol != -1) return sol;
    sol = 0;
    if(stat == UP) {
        if(a == 1) 
            sol = (sol + DFS(h + 1, w, 2, 0, UP)) % MOD;
        else {
            sol = (sol + DFS(h + 1, w, 2, 0, UP)) % MOD;
            sol = (sol + DFS(h, w + 1, 0, 1, LEFT)) % MOD;
        }
    } else if(stat == LEFT) {
        if(b == 1)
            sol = (sol + DFS(h, w + 1, 0, 2, LEFT)) % MOD;
        else {
            sol = (sol + DFS(h + 1, w, 1, 0, UP)) % MOD;
            sol = (sol + DFS(h, w + 1, 0, 2, LEFT)) % MOD;
        }
    }
    else if(stat == ALL) {
        sol = (sol + DFS(h + 1, w, 2, 0, UP)) % MOD;
        sol = (sol + DFS(h, w + 1, 0, 2, LEFT)) % MOD;
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> W >> H;
    memset(dp, -1, sizeof(dp));
    cout << DFS(1, 1, 1, 1, ALL) << '\n';
    return 0;
}