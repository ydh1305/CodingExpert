#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

struct Data {
    int h;
    int p;
};
Data D[300000];

int N, S;
int dp[300000];

int lower_bound(int s, int e, int v) {
    while(s <= e) {
        int m = (s + e) / 2;
        if(D[m].h < v) s = m + 1;
        else e = m - 1;
    }
    return e;
}

int DFS(int n) {
    if(n == N) return 0;
    int& sol = dp[n];
    if(sol != -1) return sol;
    sol = 0;
    int v = D[n].h + S;
    int idx = lower_bound(n, N - 1, v);
    sol = max(sol, DFS(idx + 1) + D[n].p);
    sol = max(sol, DFS(n + 1));
    return sol;
}

bool comp(const struct Data &a, const struct Data &b) {
    return a.h < b.h; 
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> S;
    memset(dp, -1, sizeof(dp));
    for(int i = 0; i < N; ++i)
        cin >> D[i].h >> D[i].p;
    sort(D, D + N, comp);
    cout << DFS(0) << '\n';
    return 0;
}