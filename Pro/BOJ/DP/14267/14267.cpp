#include <iostream>
#include <vector>
using namespace std;

vector<int> v[100001];
int dp[100001];
bool visit[100001];

void DFS(int n, int m) {
    dp[n] = dp[n] + m;
    for(int i = 0; i < v[n].size(); ++i) {
        int next = v[n][i];
        DFS(next, dp[n]);
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int N, M; cin >> N >> M;
    for(int i = 1; i <= N; ++i) {
        int x; cin >> x;
        if(i == 1) continue;
        v[x].push_back(i);
    }
    for(register int i = 0; i < M; ++i) {
        int a, b; cin >> a >> b;
        dp[a] = dp[a] + b;
    }
    DFS(1, 0);
    for(int i = 1; i <= N; ++i)
        cout << dp[i] << ' ';
    cout << '\n';
    return 0;
}