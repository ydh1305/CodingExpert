#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int N, sol, len, min_i;
vector<int> s, e;
vector<int> v[10001];
int dp[10001];
bool visit[10001];

void DFS(int n, int len) {
    visit[n] = true;
    if(sol < len) {
        sol = len;
        s.clear();
        s.push_back(n);
    }
    else if(sol == len)
        s.push_back(n);
    for(int i = 0; i < v[n].size(); ++i) {
        int next = v[n][i];
        if(visit[next]) continue;
        DFS(next, len + dp[next]);
    }
    visit[n] = false;
}

void DFS2(int start, int n, int len) {
    visit[n] = true;
    if(sol < len) {
        sol = len;
        e.clear();
        if(start < n)
            e.push_back(start);
        else 
            e.push_back(n);
    }
    else if(sol == len) {
        if(start < n)
            e.push_back(start);
        else
            e.push_back(n);
    }
    for(int i = 0; i < v[n].size(); ++i) {
        int next = v[n][i];
        if(visit[next]) continue;
        DFS2(start, next, len + dp[next]);
    }
    visit[n] = false;
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
    DFS(1, dp[1]);
    sol = 0;
    for(int i = 0; i < s.size(); ++i)
        DFS2(s[i], s[i], dp[s[i]]);
    sort(e.begin(), e.end());
    cout << sol << ' ' << e[0];
    return 0;
}