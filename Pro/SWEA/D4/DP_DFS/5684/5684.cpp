#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

vector<int> v[401];
int dist[401][401];
bool visit[401];
int check[401];
long long sol;

void DFS(int cur, int n, long long sum) {
    visit[n] = true;
    for(int i = 0; i < v[n].size(); ++i) {
        int next = v[n][i];
        if(!visit[next]) {
            if(sum + dist[n][next] < sol) 
                DFS(cur, next, sum + dist[n][next]);
        }
        else if(cur == next) 
            sol = min(sol, sum + dist[n][next]);
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int N, M; cin >> N >> M;
        for(int i = 1; i <= N; ++i) {
            check[i] = 0;
            v[i].clear();
            for(int j = 1; j <= N; ++j)
                dist[i][j] = 0;
        }
        for(int i = 0; i < M; ++i) {
            int s, e, c; cin >> s >> e >> c;
            v[s].push_back(e);
            dist[s][e] = c;
            check[e]++;
        }
        sol = 987654321;
        for(int i = 1; i <= N; ++i) {
            if(!check[i]) continue;
            memset(visit, false, sizeof(visit));
            DFS(i, i, 0);
        }
        if(sol == 987654321) sol = -1;
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}