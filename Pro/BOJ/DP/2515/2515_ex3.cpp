#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

struct Pic {
    int h;
    int p;
};
Pic P[300000];

int N, S;
int dp[300000];

bool comp(const struct Pic &a, const struct Pic &b) {
    return a.h < b.h;
}

int lower_bound(int s, int e, int v) {
    while(s < e) {
        int m = (s + e) / 2;
        if(P[m].h < v) s = m + 1;
        else e = m;
    }
    return e;
}

int DFS(int n) {
    if(n == N) return 0;
    int& sol = dp[n];
    if(sol != -1) return sol;
    sol = 0;
    int idx = lower_bound(n, N, P[n].h + S);
    sol = max(sol, DFS(idx) + P[n].p);
    sol = max(sol, DFS(n + 1));
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> S;
    for(int i = 0; i < N; ++i)
        cin >> P[i].h >> P[i].p;
    sort(P, P + N, comp);
    memset(dp, -1, sizeof(dp));
    cout << DFS(0) << '\n';
    return 0;
}