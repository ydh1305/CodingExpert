#include <iostream>
#include <cstring>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int N, K;
int dp[8];
char str[29];

int cal(int n) {
    if(dp[n]) return dp[n];
    dp[0] = 1;
    dp[1] = 16;
    for(int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] * 16;
    }
    return dp[n];
}

int conv(char *a, int *b) {
    int i = 0;
    for(; a[i]; ++i) {
        if(a[i] >= 'A') b[i] = a[i] - 'A' + 10;
        else b[i] = a[i] - '0';
    }
    return i; 
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N >> K;
        cin >> str;
        int len = strlen(str);
        int d = len / 4;
        char tmp[8];
        set<string> S;
        for(int i = 0; i < len; ++i) {
            int s = i;
            for(int j = 0; j < d; ++j) {
                tmp[j] = str[s++];
                if(s == len) s = 0;
            }
            tmp[d] = '\0';
            S.insert(tmp);
        }
        int n;
        vector<string> v;
        for(auto n : S)
            v.push_back(n);
        sort(v.begin(), v.end(), greater<string>());
        int S1[8] = { 0, };
        for(int i = 0; v[K - 1][i]; ++i)
            tmp[i] = v[K - 1][i];
        len = conv(tmp, S1);
        int sol = 0; n = 0; 
        for(int i = len - 1; i >= 0; --i)
            sol = sol + (S1[i] * cal(n++));
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}