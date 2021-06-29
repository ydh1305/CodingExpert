#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

struct Food {
    int a;
    int b;
    int c;
};
Food F[41], S;
bool visit[41];
bool dp[42][51][51][51];
int N;
int ans[41];
int ans_cnt;
vector<int> temp;
vector<int> sol;

void DFS(int n, int a, int b, int c, int cnt) {
    if(ans_cnt <= cnt) return;
    if(S.a < a || S.b < b || S.c < c) return;
    if(cnt > N) return;
    if(S.a == a && S.b == b && S.c == c) {
        ans_cnt = cnt;
        sol.clear();
        for(int j = 0; j < temp.size(); j++)
            sol.push_back(temp[j]);
    }
    if(dp[n][a][b][c]) return;
    dp[n][a][b][c] = true;
    for(int i = n; i <= N; ++i) {
        if(visit[i]) continue;
        visit[i] = true;
        temp.push_back(i);
        if(a + F[i].a <= 50 && b + F[i].b <= 50 && c + F[i].c <= 50)
            DFS(i + 1, a + F[i].a, b + F[i].b, c + F[i].c, cnt + 1);
        temp.pop_back();
        visit[i] = false;
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N;
        for(int i = 1; i <= N; ++i)
            cin >> F[i].a >> F[i].b >> F[i].c;
        cin >> S.a >> S.b >> S.c;
        ans_cnt = 41;
        temp.clear();
        memset(dp, false, sizeof(dp));
        DFS(1, 0, 0, 0, 0);
        cout << '#' << t << ' ';
        sort(sol.begin(), sol.end());
        if(sol.size()) {
            for(int i = 0; i < sol.size(); ++i)
                cout << sol[i] << ' ';
            cout << '\n';
        }
        else cout << 0 << '\n';
    }
    return 0;
}