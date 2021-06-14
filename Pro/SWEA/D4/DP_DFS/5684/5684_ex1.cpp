#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define INF 987654321

int N, M, nS;
long long sol;
long long dist[401][401];
bool visit[401];
vector<int> v[401];

void DFS(int s, int cur, long long len) {
    visit[cur] = true;
    for(int i = 0; i < v[cur].size(); ++i) {
        int next = v[cur][i];
        if(!visit[next]) {
            if(sol > len + dist[cur][next])
                DFS(s, next, len + dist[cur][next]);
        }
        else if(s == next) {
            sol = min(sol, len + dist[cur][next]);
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N >> M;
        nS = 0;
        for(int i = 1; i <= N; ++i) {
            v[i].clear();
            for(int j = 1; j <= N; ++j)
                dist[i][j] = dist[j][i] = 0;
        }
        vector<int> pos;
        for(int i = 0; i < M; ++i) {
            int s, e, c; cin >> s >> e >> c;
            dist[s][e] = c;
            v[s].push_back(e);
            pos.push_back(s);
        }
        sol = INF;
        for(int i = 0; i < pos.size(); ++i) {
            DFS(pos[i], pos[i], 0);
            memset(visit, false, sizeof(visit));
        }
        if(sol == INF) sol = -1;
        cout << '#' << t << ' ' << sol << '\n'; 
    }
    return 0;
}