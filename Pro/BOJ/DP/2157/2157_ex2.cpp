#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define INF 987654321

int N, M, K;
int dist[301][301];
int dp[301][301];
vector<int> v[301];
bool visit[301][301];

int DFS(int cur, int len) {
    if(len == M && cur != N) return -INF;
    if(cur == N) return 0;
    int& sol = dp[cur][len];
    if(sol != -1) return sol;
    sol = -INF;
    for(int i = 0; i < v[cur].size(); ++i) {
        int next = v[cur][i];
        sol = max(sol, DFS(next, len + 1) + dist[cur][next]);
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M >> K;
    for(int i = 0; i < K; ++i) {
        int a, b, c; cin >> a >> b >> c;
        if(a > b) continue;
        if(dist[a][b] < c)
            dist[a][b] = c;
        if(!visit[a][b]) {
            visit[a][b] = true;
            v[a].push_back(b);
        }
    }
    memset(dp, -1, sizeof(dp));
    cout << DFS(1, 1) << '\n';
    return 0;
}