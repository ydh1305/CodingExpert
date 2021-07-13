#include <iostream>
#include <vector>
using namespace std;

int N, sol, idx;
vector<pair<int,int>> v[10001];


void DFS(int cur, int prev, int len) {
    if(sol < len) {
        sol = len;
        idx = cur;
    }
    for(int i = 0; i < v[cur].size(); ++i) {
        pair<int,int> next = v[cur][i];
        if(prev == next.first) continue;
        DFS(next.first, cur, len + next.second);
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    for(int i = 0; i < N - 1; ++i) {
        int a, b, d; cin >> a >> b >> d;
        v[a].push_back({b, d}); v[b].push_back({a, d});
    }
    DFS(1, 1, 0);
    sol = 0;
    DFS(idx, idx, 0);
    cout << sol << '\n';
    return 0;
}