#include <bits/stdc++.h>
using namespace std;

pair<int, int> v[1000001];

int comp(const pair<int, int> &a, const pair<int, int> &b) {
    return a.first > b.first;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int N; cin >> N;
        vector<bool> visit(N + 1, false);
        for(int j = 0; j < N; j++) {
            int x; cin >> x;
            v[j] = {x, j + 1};
        }
        sort(v, v + N, comp);
        int cnt = 0;
        long long sum = 0;
        queue<int> q;
        int n = 0;
        while(cnt != N) {
            int q_size = q.size();
            for(int j = 0; j < q_size; j++) {
                int idx = q.front(); q.pop();
                if(!visit[idx]) {
                    visit[idx] = true;
                    cnt++;
                    if(idx == 1) q.push(idx + 1);
                    else if(idx == N) q.push(idx - 1);
                    else {
                        q.push(idx - 1); q.push(idx + 1);
                    }
                }
            }
            while(n < N) {
                if(!visit[v[n].second]) {
                    visit[v[n].second] = true;
                    sum = sum + v[n].first;
                    if(v[n].second == 1) q.push(v[n].second + 1);
                    else if(v[n].second == N) q.push(v[n].second - 1);
                    else {
                        q.push(v[n].second - 1); q.push(v[n].second + 1);
                    }
                    cnt++; n++;
                    break;
                }
                n++;
            }
        }
        cout << '#' << i << ' ' << sum << '\n';
    }
    return 0;
}