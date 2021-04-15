#include <bits/stdc++.h>
using namespace std;

int comp1(const pair<pair<int, int>, pair<int, int>> &a, const pair<pair<int, int>, pair<int, int>> &b) {
    if(a.second.first == b.second.first) {
        if(a.first.first == b.first.first)
            return a.first.second > a.first.second;
        return a.first.first > b.first.first;
    }
    return a.second.first > b.second.first;
}

int comp2(const pair<pair<int, int>, pair<int, int>> &a, const pair<pair<int, int>, pair<int, int>> &b) {
    if(a.second.first == b.second.first) {
        if(a.first.second == b.first.second)
            return a.first.first > a.first.first;
        return a.first.second > b.first.second;
    }
    return a.second.first > b.second.first;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int N; cin >> N;
        vector<pair<pair<int, int>, pair<int, int>>> v1;
        vector<pair<pair<int, int>, pair<int, int>>> v2;
        for(int j = 1; j <= N; j++) {
            int a, b; cin >> a >> b;
            v1.push_back({{a, b},{(b > a) ? b : a, j}});
            v2.push_back({{a, b},{(a > b) ? a : b, j}});
        }
        sort(v1.begin(), v1.end(), comp1);
        sort(v2.begin(), v2.end(), comp2);
        vector<bool> visit(N + 1, false);
        long long s1 = 0, s2 = 0;
        int s = 0, e = 0, id = 0;
        while(s < N && e < N) {
            while(s < N) {
                id = v1[s].second.second;
                if(!visit[id]) break;
                s++;
            }
            visit[id] = true;
            s1 = s1 + v1[s].first.first;
            s++;
            while(e < N) {
                id = v2[e].second.second;
                if(!visit[id]) break;
                e++;
            }
            visit[id] = true;
            s2 = s2 + v2[e].first.second;
            e++;
        }
        cout << '#' << i << ' ' << s1 - s2 << '\n';
    }
    return 0;
}