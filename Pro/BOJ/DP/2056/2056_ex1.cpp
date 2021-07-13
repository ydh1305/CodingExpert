#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int N;
vector<int> v[10001];
int dp[10001];
int dist[10001];

int DFS(int cur) {
    int& sol = dp[cur];
    if(sol != -1) return sol;
    sol = dist[cur];
    int tmp = 0;
    for(int i = 0; i < v[cur].size(); ++i) {
        int next = v[cur][i];
        tmp = max(tmp, DFS(next));
    }
    sol = sol + tmp;
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    memset(dp, -1, sizeof(dp));
    for(int i = 1; i <= N; ++i) {
        cin >> dist[i];
        int x; cin >> x;
        for(int j = 0; j < x; ++j) {
            int a; cin >> a;
            v[i].push_back(a);
        }
    }
    int ans = 0;
    for(int i = 1; i <= N; ++i)
        ans = max(ans, DFS(i));
    cout << ans << '\n';
    return 0;
}