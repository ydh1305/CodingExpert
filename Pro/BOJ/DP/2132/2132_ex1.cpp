#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, sol;
int dp[10001];
vector<int> v[10001];
vector<int> v1, v2;

void DFS(int cur, int prev, int len) {
    if(sol < len) {
        sol = len;
        v1.clear();
        v1.push_back(cur);
    }
    else if(sol == len)
        v1.push_back(cur);
    for(int i = 0; i < v[cur].size(); ++i) {
        int next = v[cur][i];
        if(prev == next) continue;
        DFS(next, cur, len + dp[next]);
    }
}

void DFS2(int start, int cur, int prev, int len) {
    if(sol < len) {
        sol = len;
        v2.clear();
        if(start < cur)
            v2.push_back(start);
        else 
            v2.push_back(cur);
    }
    else if(sol == len) {
        if(start < cur)
            v2.push_back(start);
        else 
            v2.push_back(cur);
    }
    for(int i = 0; i < v[cur].size(); ++i) {
        int next = v[cur][i];
        if(prev == next) continue;
        DFS2(start, next, cur, len + dp[next]);
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    for(int i = 1; i <= N; ++i)
        cin >> dp[i];
    for(int i = 0; i < N - 1; ++i) {
        int a, b; cin >> a >> b;
        v[a].push_back(b); v[b].push_back(a);
    }
    DFS(1, 1, dp[1]);
    sol = 0;
    for(int i = 0; i < v1.size(); ++i) {
        DFS2(v1[i], v1[i], v1[i], dp[v1[i]]);
    }
    sort(v2.begin(), v2.end());
    cout << sol << ' ' << v2[0] << '\n';
    return 0;
}