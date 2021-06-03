#include <iostream>
using namespace std;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int N, P; cin >> N >> P;
        int d = N / P;
        int r = N % P;
        long long sol = 1;
        if(r == 0) {
            for(int i = 0; i < P; ++i)
                sol = sol * d;
        }
        else {
            for(int i = 0; i < P - r; ++i)
                sol = sol * d;
            for(int i = P - r; i < P; ++i)
                sol = sol * (d + 1);
        }
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}