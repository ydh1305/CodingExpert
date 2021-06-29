#include <iostream>
#include <vector>
using namespace std;

vector<int> v[1001];
int dist[1001][1001];
bool visit[1001];

void DFS(int s, int cur, int e, int len) {
    if(cur == e) return;  
    visit[cur] = true;
    for(int i = 0; i < v[cur].size(); ++i) {
        int next = v[cur][i];
        if(visit[next]) continue;
        dist[s][next] = dist[cur][next] + len;
        DFS(s, next, e, dist[cur][next] + len);
    }
    visit[cur] = false;
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
        DFS(a, a, b, 0);
        cout << dist[a][b] << '\n';
    }
    return 0;
}