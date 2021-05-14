#include <bits/stdc++.h>
using namespace std;

int dp[8];

int cal(int cnt) {
    if(dp[cnt]) return dp[cnt];
    if(cnt == 0) dp[cnt] = 1;
    else dp[cnt] = dp[cnt - 1] * 16;
    return dp[cnt];
}

void conv(int *S, char *C) {
    for(int i = 0; C[i]; i++) {
        if(C[i] >= 'A') S[i] = C[i] - 'A' + 10;
        else S[i] = C[i] - '0';
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; t++) {
        int N, K, sol; cin >> N >> K;
        int d = N / 4;
        char str[29]; cin >> str;
        char tmp[8];
        int it;
        set<string> st;
        vector<string> v;
        for(int i = 0; i < N; i++) {
            int s = i, idx = 0;
            for(int j = 0; j < d; j++) {
                if(s == N) s = 0;
                tmp[idx++] = str[s++];
            }
            tmp[idx] = '\0';
            st.insert(tmp);
        }
        for(auto it : st)
            v.push_back(it);
        sort(v.begin(), v.end(), greater<string>());        
        int S[8];
        char C[8];
        int len = v[K - 1].length();
        int i = 0;
        for(; i < len; i++)
            C[i] = v[K - 1][i];
        C[i] = '\0';
        conv(S, C);
        sol = 0;
        int k = 0;
        for(i = len - 1; i >= 0; i--)
            sol = sol + S[i] * cal(k++);
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}