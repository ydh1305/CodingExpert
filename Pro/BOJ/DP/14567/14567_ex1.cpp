#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int N, M;
int dp[1001];
vector<int> v[1001];

int DFS(int n) {
    int& sol = dp[n];
    if(sol != -1) return sol;
    sol = 1;
    int cnt = 0;
    for(int i = 0; i < v[n].size(); ++i) {
        int next = v[n][i];
        cnt = max(cnt, DFS(next)); 
    }
    sol = sol + cnt;
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for(int i = 0; i < M; ++i) {
        int a, b; cin >> a >> b;
        v[b].push_back(a);
    }
    memset(dp, -1, sizeof(dp));
    for(int i = 1; i <= N; ++i)
        cout << DFS(i) << ' ';
    return 0;
}