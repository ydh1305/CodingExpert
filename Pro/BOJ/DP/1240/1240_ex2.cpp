#include <iostream>
#include <vector>
using namespace std;

int N, M;
int dist[1001][1001];
vector<int> v[1001];

void DFS(int s, int cur, int prev, int tar, int len) {
    if(tar == cur) return;
    for(int i = 0; i < v[cur].size(); ++i) {
        int next = v[cur][i];
        if(prev == next) continue;
        dist[s][next] = dist[s][cur] + dist[cur][next];
        DFS(s, next, cur, tar, len + dist[s][next]);
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for(int i = 0; i < N - 1; ++i) {
        int a, b, c; cin >> a >> b >> c;
        dist[a][b] = dist[b][a] = c;
        v[a].push_back(b); v[b].push_back(a);
    }
    for(int i = 0; i < M; ++i) {
        int a, b; cin >> a >> b;
        DFS(a, a, a, b, 0);
        cout << dist[a][b] << '\n';
    }
    return 0;
}