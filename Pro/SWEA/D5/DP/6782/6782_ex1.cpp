#include <bits/stdc++.h>
using namespace std;

long long sol;
long long DFS(long long val) {
    if(val == 2) return sol;
    if(val + 1 == 2) return sol + 1;
    long long num = sqrt(val);
    if(num * num == val) {
        sol = sol + 1;
        DFS(num);
    }
    else {
        sol = sol + ((num + 1) * (num + 1) - val) + 1;
        DFS(num + 1);
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        long long N; cin >> N;
        sol = 0;
        cout << '#' << i << ' ' << DFS(N) << '\n';
    }
    return 0;
}