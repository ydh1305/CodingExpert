#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> v[501];
int dp[501];
int dist[501];

int DFS(int n) {
    int& sol = dp[n];
    if(sol) return sol;
    sol = dist[n];
    int tmp = 0;
    for(int i = 0; i < v[n].size(); ++i) {
        int next = v[n][i];
        tmp = max(tmp, DFS(next));
    }
    sol = sol + tmp;
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    for(int i = 1; i <= N; ++i) {
        cin >> dist[i];
        while(1) {
            int x; cin >> x;
            if(x == -1) break;
            v[i].push_back(x);
        }
    }
    for(int i = 1; i <= N; ++i)
        cout << DFS(i) << '\n';
    return 0;
}