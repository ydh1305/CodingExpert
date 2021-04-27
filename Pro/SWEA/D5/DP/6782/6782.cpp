#include <bits/stdc++.h>
using namespace std;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        long long N; cin >> N;
        queue<pair<long long, long long>> q;
        q.push({N, 0});
        long long sum = 0;
        while(!q.empty()) {
            pair<long long, long long> v = q.front(); q.pop();
            if(v.first == 2) {
                sum = v.second;
                break;
            }
            q.push({v.first + 1, v.second + 1});
            long double num = sqrt((long double)v.first);
            if(num - (long long)num == 0) 
                q.push({(long long)num, v.second + 1});
        }
        cout << '#' << i << ' ' << sum << '\n';
    }
    return 0;
}