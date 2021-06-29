#include <iostream>
#include <vector>
using namespace std;

vector<int> v[1001];
int dist[1001][1001];

void DFS(int s, int cur, int prev, int e, int len) {
    if(cur == e) return;
    for(int i = 0; i < v[cur].size(); ++i) {
        int next = v[cur][i];
        if(prev == next) continue;
        dist[s][next] = dist[cur][next] + len;
        DFS(s, next, cur, e, dist[cur][next] + len);
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int N, M; cin >> N >> M;
    for(int i = 0; i < N - 1; ++i) {
        int a, b, d; cin >> a >> b >> d;
        v[a].push_back(b); v[b].push_back(a);
        dist[a][b] = dist[b][a] = d;
    }
    for(int i = 0; i < M; ++i) {
        int a, b; cin >> a >> b;
        DFS(a, a, -1, b, 0);
        printf("%d\n", dist[a][b]);
        cout << dist[a][b] << '\n';
    }
    return 0;
}