#include <bits/stdc++.h>
using namespace std;

#define MAX 100000
long long S[MAX + 1];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int N, H; cin >> N >> H;
        int idx = -1;
        int sum = 0;
        for(register int j = 1; j <= N; j++) {
            int x; cin >> x;
            S[j] = S[j - 1] + x;
        }
        for(int j = 1; j <= N; j++) {
            int x; cin >> x;
            if(!x) {
                if(j == 1 || j == N) {
                    sum++;
                    idx = j;
                    continue;
                }
                if(S[j] - S[idx] >= H) {
                    sum++;
                    idx = j;
                }
            }
            else if(x == 1) idx = j;
        }
        cout << '#' << i << ' ' << sum << '\n'; 
    }
    return 0;
}