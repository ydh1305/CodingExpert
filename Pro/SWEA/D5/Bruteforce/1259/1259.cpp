#include <iostream>
#include <vector>
using namespace std;

int _next[40], _prev[40];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int N; cin >> N;
        int x, y; 
        for(int i = 0; i < N; ++i) {
            cin >> x >> y;
            _next[x] = y;
            _prev[y] = x;
        }
        int cur = y;
        while(true) {
            if(_prev[cur] == 0) break;
            cur = _prev[cur];
        }
        cout << '#' << t << ' ';
        while(true) {
            if(_next[cur] == 0) break;
            cout << cur << ' ' << _next[cur] << ' ';
            cur = _next[cur]; 
        }
        cout << '\n';
        for(int i = 0; i < 40; ++i) {
            _next[i] = _prev[i] = 0;
        }
    }
    return 0;
}