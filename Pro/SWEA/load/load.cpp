#include <iostream>
#include <cstring>
using namespace std;

struct Box {
    int w;
    int h;
    int sum;
};
Box box[100];
int dp[100][10001];
int N, W, sol;

int DFS(int n, int wid, int sum) {
    if(n == N) {
        if(wid == W)
            sol = max(sol, sum);
        return sol;
    }
    int& ret = dp[n][wid];
    if(ret != -1) return ret;
    ret = 0;
    if(wid + box[n].h <= W)
        ret = max(ret, DFS(n + 1, wid + box[n].h, sum + box[n].sum));
    if(wid + box[n].w <= W)
        ret = max(ret, DFS(n + 1, wid + box[n].w, sum + box[n].sum));
    ret = max(ret, DFS(n + 1, wid, sum));
    return ret;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N >> W;
        for(int i = 0; i < N; ++i) {
            cin >> box[i].h >> box[i].w;
            box[i].sum = box[i].h * box[i].w;
        }
        memset(dp, -1, sizeof(dp));
        sol = 0; 
        cout << '#' << t << ' ' << DFS(0, 0, 0) << '\n';
    }
    return 0;
}