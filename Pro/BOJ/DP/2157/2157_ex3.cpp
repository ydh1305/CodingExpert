#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define INF 987654321

int N, M, K;
vector<int> v[301];
int dist[301][301];
bool visit[301][301];
int dp[301][301];

int DFS(int n, int cnt) {
    if(n != N && cnt == M) return -INF;
    if(n == N) return 0;
    int& sol = dp[n][cnt];
    if(sol != -1) return sol;
    sol = -INF;
    for(int i = 0; i < v[n].size(); ++i) {
        int next = v[n][i];
        sol = max(sol, DFS(next, cnt + 1) + dist[n][next]);
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M >> K;
    memset(dp, -1, sizeof(dp));
    for(int i = 0; i < K; ++i) {
        int a, b, d; cin >> a >> b >> d;
        if(a > b) continue;
        if(dist[a][b] < d)
            dist[a][b] = d;
        if(!visit[a][b]) {
            visit[a][b] = true;
            v[a].push_back(b);
        }
    }
    cout << DFS(1, 1) << '\n';
}