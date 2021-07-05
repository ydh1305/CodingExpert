#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int N;
int S[10001];
int dp[10001][2];
vector<int> v[10001];

int DFS(int cur, int prev, bool sel) {
    int& sol = dp[cur][sel];
    if(sol != -1) return sol;
    if(sel) sol = S[cur];
    else sol = 0;
    for(int i = 0; i < v[cur].size(); ++i) {
        int next = v[cur][i];
        if(prev == next) continue;
        if(!sel)
            sol = sol + max(DFS(next, cur, 0), DFS(next, cur, 1));
        else 
            sol = sol + DFS(next, cur, 0);
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    memset(dp, -1, sizeof(dp));
    for(int i = 1; i <= N; ++i)
        cin >> S[i];
    for(int i = 0; i < N - 1; ++i) {
        int a, b; cin >> a >> b;
        v[a].push_back(b); v[b].push_back(a);
    }
    cout << max(DFS(1, 1, 0), DFS(1, 1, 1)) << '\n';
    return 0;
}