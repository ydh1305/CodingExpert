#include <iostream>
#include <vector>
using namespace std;

int N, sol, last_node;
vector<pair<int, int>> v[10001];
bool visit[10001];

void DFS(int n, int len) {
    visit[n] = true;
    if(sol < len) {
        sol = len;
        last_node = n;
    }
    for(int i = 0; i < v[n].size(); ++i) {
        pair<int, int> next = v[n][i];
        if(visit[next.first]) continue;
        DFS(next.first, len + next.second);
    }
    visit[n] = false;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    for(int i = 0; i < N - 1; ++i) {
        int x, y, d; cin >> x >> y >> d;
        v[x].push_back({y, d});
        v[y].push_back({x, d});
    }
    DFS(1, 0);
    DFS(last_node, 0);
    cout << sol << '\n';
    return 0;
}