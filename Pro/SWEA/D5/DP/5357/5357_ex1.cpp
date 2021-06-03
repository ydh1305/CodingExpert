#include <iostream>
using namespace std;

long long S[100001];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int N, H; cin >> N >> H;
        for(int i = 1; i <= N; ++i) {
            int x; cin >> x;
            S[i] = S[i - 1] + x;
        }
        int s = 0;
        int sol = 0;
        for(int i = 1; i <= N; ++i) {
            int x; cin >> x;
            if(x) s = i;
            else {
                if(i == 1 || i == N) {
                    s = i;
                    sol = sol + 1;
                    continue;
                }
                if(S[i] - S[s] >= H) {
                    s = i;
                    sol = sol + 1;
                }
            }
        }
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}