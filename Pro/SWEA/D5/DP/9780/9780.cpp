#include <bits/stdc++.h>
using namespace std;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int N; cin >> N;
        priority_queue<pair<int, int>> pq;
        vector<bool> visit(N + 1, false);
        for(int j = 1; j <= N; j++) {
            int x; cin >> x;
            pq.push({x, j});
        }
        int cnt = 0;
        long long sum = 0;
        pair<int, int> val;
        queue<int> q;
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
            while(!pq.empty()) {
                val = pq.top(); pq.pop();
                if(!visit[val.second]) {
                    visit[val.second] = true;
                    cnt++;
                    sum = sum + val.first;
                    if(val.second == 1) q.push(val.second + 1);
                    else if(val.second == N) q.push(val.second - 1);
                    else {
                        q.push(val.second - 1); q.push(val.second + 1);
                    }
                    break;
                }
            }
        }
        cout << '#' << i << ' ' << sum << '\n';
    }
    return 0;
}