#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

struct Paper {
    int x;
    int y;
};
Paper P[100];
int dp[100];
int N;

bool comp(const struct Paper &a, const struct Paper &b) {
    return (a.x * a.y) < (b.x * b.y);
}

int DFS(int n, int x, int y) {

    int& sol = dp[n];
    if(sol != -1) return sol;
    sol = 0;
    for(int i = n; i < N; ++i) {
        if((x <= P[i].x && y <= P[i].y) || (x <= P[i].y && y <= P[i].x))
            sol = max(sol, DFS(i + 1, P[i].x, P[i].y) + 1);
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    for(int i = 0; i < N; ++i)
        cin >> P[i].x >> P[i].y;
    sort(P, P + N, comp);
    memset(dp, -1, sizeof(dp));
    cout << DFS(0, 0, 0) << '\n';
    return 0;
}