#include <bits/stdc++.h>
using namespace std;

long long N;
long long bs_search(long long s, long long e) {
    while(s <= e) {
        long long m = (s + e) / 2;
        long double num = (long double)N / (long double)(m + 1);
        long double k = (long double)m / 2.0;
        if(k == num) return m;
        else if(k < num) s = m + 1;
        else e = m - 1;
    }
    return -1;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(register int i = 1; i <= T; i++) {
        cin >> N;
        cout << '#' << i << ' ' << bs_search(1, N) << '\n';
    }
    return 0;
}