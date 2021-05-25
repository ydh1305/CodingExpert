#include <iostream>
using namespace std;

long long binary_search(int s, long long e) {
    long double val = e;
    long long sol = -1;
    while(s <= e) {
        long double m = (s + e) / 2;
        long double x = (m * (m + 1)) / 2;
        if(val == x) {
            sol = m;
            break;
        }
        else if(val < x) {
            e = m - 1;
        }
        else if(val > x) {
            s = m + 1;
        }
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; t++) {
        long long N; cin >> N;
        cout << '#' << t << ' ' << binary_search(0, N) << '\n';
    }
    return 0;
}