#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define MOD 1000000007
#define WH 0
#define BL 1

vector<int> v[100001];
long long dp[100001][2];
bool visit[100001];

long long DFS(int n, int c) {
    long long& sol = dp[n][c];
    if(sol != -1) return sol;
    sol = 1;
    visit[n] = true;
    for(int i = 0; i < v[n].size(); ++i) {
        int next = v[n][i];
        if(!visit[next]) {
            if(c == WH)
                sol = (sol * (DFS(next, WH) + DFS(next, BL))) % MOD;
            else 
                sol = (sol * DFS(next, WH)) % MOD;
        }
    }
    visit[n] = false;
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int N; cin >> N;
        for(int i = 1; i <= N; ++i) {
            v[i].clear();
            dp[i][0] = dp[i][1] = -1;
        }
        for(int i = 0; i < N - 1; ++i) {
            int x, y; cin >> x >> y;
            v[x].push_back(y); v[y].push_back(x);
        }
        cout << '#' << t << ' ' << (DFS(1, WH) + DFS(1, BL)) % MOD << '\n';
    }
    return 0;
}