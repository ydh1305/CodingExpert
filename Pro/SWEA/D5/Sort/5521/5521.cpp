#include <bits/stdc++.h>
using namespace std;

bool visit[10001], check[10001];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int N, M; cin >> N >> M;
        pair<int, int> v[10001];
        int cnt = 0;
        memset(check, 0, sizeof(check));
        memset(visit, 0, sizeof(visit));
        for(int j = 0; j < M; j++) {
            cin >> v[j].first >> v[j].second;
            if(v[j].first == 1) 
                check[v[j].second] = true;
        }
        sort(v, v + M);
        visit[1] = true;
        for(int j = 0; j < M; j++) {
            if(check[v[j].first] || check[v[j].second]) {
                if(!visit[v[j].first]) {
                    visit[v[j].first] = true;
                    cnt++;
                }
                if(!visit[v[j].second]) {
                    visit[v[j].second] = true;
                    cnt++;
                }
            }
        }
        cout << '#' << i << ' ' << cnt << '\n';
    }
    return 0;
}