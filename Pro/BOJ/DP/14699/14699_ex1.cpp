#include <iostream>
#include <vector>
using namespace std;

int N, M, sol;
int node[5001];
int dp[5001];
bool visit[5001];
vector<int> v[5001];

int DFS(int cur) {
    if(dp[cur]) return dp[cur];
    dp[cur] = 1;
    visit[cur] = true;
    for(int i = 0; i < v[cur].size(); ++i) {
        int next = v[cur][i];
        if(visit[next]) continue;
        if(node[cur] < node[next])
            dp[cur] = max(dp[cur], DFS(next) + 1);
    }
    visit[cur] = false;
    return dp[cur];
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for(int i = 1; i <= N; ++i)
        cin >> node[i];
    for(int i = 0; i < M; ++i) {
        int a, b; cin >> a >> b;
        if(node[a] < node[b])
            v[a].push_back(b);
        if(node[b] < node[a])
            v[b].push_back(a);
    }
    for(int i = 1; i <= N; ++i)
        cout << DFS(i) << '\n';
    return 0;
}