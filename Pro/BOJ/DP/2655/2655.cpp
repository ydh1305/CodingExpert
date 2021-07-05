#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

struct Brick {
    int idx;
    int d;
    int h;
    int w;
};
Brick B[101];

int N, total;
int dp[101];
int pos[101];

bool comp(const struct Brick &a, const struct Brick &b) {
    return a.d > b.d;
}

int DFS(int n) {
    int& sol = dp[n];
    if(sol != -1) return sol;
    sol = B[n].h;
    for(int i = n + 1; i <= N; ++i) {
        if(B[n].w > B[i].w && sol < B[n].h + DFS(i)) {
            sol = DFS(i) + B[n].h;
            pos[n] = i;
        }
    }
    return sol;
}

void sol(int n, int cnt) {
    if(n == 0) {
        cout << cnt << '\n';
        return;
    }
    sol(pos[n], cnt + 1);
    cout << B[n].idx << '\n';
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    for(int i = 1; i <= N; ++i) {
        cin >> B[i].d >> B[i].h >> B[i].w;
        B[i].idx = i;
    }
    sort(B + 1, B + 1 + N, comp);
    memset(dp, -1, sizeof(dp));
    B[0].w = 987654321;
    DFS(0);
    sol(pos[0], 0);
    return 0;
}