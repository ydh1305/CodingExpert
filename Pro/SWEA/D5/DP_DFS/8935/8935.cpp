#include <bits/stdc++.h>
using namespace std;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int N; cin >> N;
        list<int> l;
        for(int j = 0; j < N; j++) {
            int x; cin >> x;
            l.push_back(x);
        }
#if 1
        list<int>::iterator it;
        for(it = l.begin(); it != l.end(); it++) {
            int prev = *it;
            int cur = *it;
            cout << "test " << prev << ' ' << cur << '\n';
        }
            //cout << "test1 " << *it << '\n';
#endif
        int M; cin >> M;
        vector<int> v;
        for(int j = 0; j < M; j++) {
            int x; cin >> x;
            v.push_back(x);
        }
        sort(v.begin(), v.end());
    }
    return 0;
}