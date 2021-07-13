#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

struct Brick {
    int idx;
    int width;
    int high;
    int weight;
};
Brick B[101];

int N;
int dp[101];
int pos[101];

bool comp(const struct Brick &a, const struct Brick &b) {
    return a.width > b.width;
}

int DFS(int n) {
    int& sol = dp[n];
    if(sol != -1) return sol;
    sol = B[n].high;
    for(int i = n + 1; i <= N; ++i) {
        if(B[i].weight < B[n].weight && sol < B[n].high + DFS(i)) {
            sol = B[n].high + DFS(i);
            pos[n] = i;
        }
    }
    return sol;
}

void solve(int n, int cnt) {
    if(n == 0) {
        cout << cnt << '\n';
        return;
    }
    solve(pos[n], cnt + 1);
    cout << B[n].idx << '\n';
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    memset(dp, -1, sizeof(dp));
    for(int i = 1; i <= N; ++i) {
        cin >> B[i].width >> B[i].high >> B[i].weight;
        B[i].idx = i;
    }
    sort(B + 1, B + 1 + N, comp);
    B[0].weight = 987654321;
    DFS(0);
    solve(pos[0], 0);
    return 0;
}