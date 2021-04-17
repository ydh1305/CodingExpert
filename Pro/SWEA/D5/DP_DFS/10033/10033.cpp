#include <bits/stdc++.h>
using namespace std;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        char str[200001];
        cin >> str;
        int cnt = 0; long long sol = 0;
        for(register int j = 0; str[j]; j++) {
            if(str[j] == 'B') cnt++;
            else if(str[j] == 'W') sol = sol + cnt;
        }
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}