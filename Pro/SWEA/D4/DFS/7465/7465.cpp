#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int N, M, sol;
vector<int> v[101];
bool visit[101];

void DFS(int n) {
    visit[n] = true;
    for(int i = 0; i < v[n].size(); ++i) {
        int next = v[n][i];
        if(visit[next]) continue;
        DFS(next);
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int N, M; cin >> N >> M;
        for(int i = 1; i <= N; ++i)
            v[i].clear();
        for(int i = 0; i < M; ++i) {
            int a, b; cin >> a >> b;
            v[a].push_back(b);
            v[b].push_back(a);
        }
        memset(visit, false, sizeof(visit));
        sol = 0;
        for(int i = 1; i <= N; ++i) {
            if(!visit[i]) {
                DFS(i);
                sol++;
            }
        }
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}