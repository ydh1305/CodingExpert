#include <bits/stdc++.h>
using namespace std;

#define MAX 200000
bool visit[MAX + 1];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int N; cin >> N;
        memset(visit, 0, sizeof)
        int sol = 0;
        for(register int j = 1; j <= N; j++) {
            int x; cin >> x;
            if(!visit[x - 1]) sol++;
            visit[x] = true;
        }
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}