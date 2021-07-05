#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

struct Brick {
    int n;
    int wid;
    int high;
    int wgt;
};
Brick B[101];

int N;
int dp[101];
int pos[101];

bool comp(const struct Brick &a, const struct Brick &b) {
    return a.wid > b.wid;
}

int DFS(int n) {
    int& sol = dp[n];
    if(sol != -1) return sol;
    sol = B[n].high;
    for(int i = n + 1; i <= N; ++i) {
        if(B[i].wgt < B[n].wgt && sol < B[n].high + DFS(i)) {
            sol = B[n].high + DFS(i);
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
    cout << B[n].n << '\n';
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    for(int i = 1; i <= N; ++i) {
        cin >> B[i].wid >> B[i].high >> B[i].wgt;
        B[i].n = i;
    }
    memset(dp, -1, sizeof(dp));
    sort(B + 1, B + 1 + N, comp);
    B[0].wgt = 987654321;
    DFS(0);
    sol(pos[0], 0);
    return 0;
}