#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int N;
int dp[501];
int B[501];
vector<int> v[501];

int DFS(int n) {
    int& sol = dp[n];
    if(sol != -1) return sol;
    sol = B[n];
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
    cin >> N;
    for(int i = 1; i <= N; ++i) {
        cin >> B[i];
        while(true) {
            int n; cin >> n;
            if(n == -1) break;
            v[i].push_back(n);
        }
    }
    memset(dp, -1, sizeof(dp));
    for(int i = 1; i <= N; ++i)
        cout << DFS(i) << '\n';
    return 0;
}