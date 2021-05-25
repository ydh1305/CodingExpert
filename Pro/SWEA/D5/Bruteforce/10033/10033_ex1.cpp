#include <iostream>
#include <cstring>
using namespace std;

char str[200001];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> str;
        int N = strlen(str);
        int cnt = 0;
        long long sol = 0;
        for(register int i = N - 1; i >= 0; --i) {
            if(str[i] == 'W') cnt = cnt + 1;
            else if(str[i] == 'B') sol = sol + cnt;
        }
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}