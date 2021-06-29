#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define MAX 1001

vector<int> v[MAX];
int dist[MAX][MAX];
bool visit[MAX];
long long sol;

void DFS(int s, int cur, long long len) {
    visit[cur] = true;
    for(int i = 0; i < v[cur].size(); ++i) {
        int e = v[cur][i];
        if(visit[e]) continue;
        dist[s][e] = dist[cur][e] + len;
        if(s < e) sol = sol + dist[s][e];
        DFS(s, e, dist[s][e]);
    }
    visit[cur] = false;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int N; cin >> N;
        for(int i = 1; i <= N; ++i)
            v[i].clear();
        for(int i = 0; i < N - 1; ++i) {
            int x, y, d; cin >> x >> y >> d;
            dist[x][y] = dist[y][x] = d;
            v[x].push_back(y); v[y].push_back(x);
        }
        sol = 0;
        for(int i = 1; i <= N; ++i)
            DFS(i, i, 0);
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}