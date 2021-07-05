#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int N;
long long dp[501];
int dist[501];
vector<int> v[501];

long long DFS(int n) {
    long long& sol = dp[n];
    if(sol) return sol;
    sol = dist[n];
    long long tmp = 0;
    for(int i = 0; i < v[n].size(); ++i) {
        int next = v[n][i];
        tmp = max(tmp, DFS(next));
    }
    sol = sol + tmp;
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    memset(dist, 0, sizeof(dist));
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= N; ++i) {
        cin >> dist[i];
        while(1) {
            int x; cin >> x;
            if(x == -1) break;
            v[i].push_back(x);
        }
    }
    for(int i = 1; i <= N; ++i)
        DFS(i);
    for(int i = 1; i <= N; ++i)
        cout << dp[i] << '\n';
    return 0;
}