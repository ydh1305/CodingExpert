#include <bits/stdc++.h>
using namespace std;

int N;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N;
        vector<string> v(3);
        for(int j = 0; j < 3; j++) {
            string s; cin >> s;
            v[j] = s;
        }
        int cnt = 0;
        for(int j = 0; j < N; j++) {
            if(v[0][j] == v[1][j] && v[1][j] == v[2][j]) continue;
            else if(v[0][j] == v[1][j] && v[1][j] != v[2][j]) cnt++;
            else if(v[0][j] != v[1][j] && v[1][j] == v[2][j]) cnt++;
            else if(v[0][j] == v[2][j] && v[2][j] != v[1][j]) cnt++;
            else cnt = cnt + 2;
        }
        cout << '#' << i << ' ' << cnt << '\n';
    }
    return 0;
}