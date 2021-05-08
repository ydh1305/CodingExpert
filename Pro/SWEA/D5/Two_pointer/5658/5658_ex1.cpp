#include <bits/stdc++.h>
using namespace std;

char str[29];
long long dp[8];
set<string> pw;
vector<string> v;

long long calc(int cnt) {
    if(cnt == 0) return 1;
    if(dp[cnt]) return dp[cnt];
    long long num = 1;
    for(int i = 0; i < cnt; i++) {
        num = num * 16;
    }
    dp[cnt] = num;
    return dp[cnt];
}

void conv(int *A, char *B) {
    for(int i = 0; B[i]; i++) {
        if(B[i] >= 'A') A[i] = B[i] - 'A' + 10;
        else A[i] = B[i] - '0';
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int N, K; cin >> N >> K;
        cin >> str;
        int d = N / 4;
        int s = 0, e = 0;
        char temp[8];
        int idx;
        pw.clear();
        v.clear();
        while(s <= N - 1) {
            idx = 0, e = s;
            for(int j = 1; j <= d; j++) {
                if(e >= N) e = 0;
                temp[idx++] = str[e++];
            }
            temp[idx] = '\0';
            pw.insert(temp);
            s++;
        }
        for(auto it = pw.begin(); it != pw.end(); it++)
            v.push_back(*it);
        sort(v.begin(), v.end(), greater<string>());
        for(int j = 0; j < v.size(); j++) {
            if(j == K - 1) {
                int len = v[j].length();
                int A[8];
                char B[8];
                int k = 0;
                for(; k < len; k++)
                    B[k] = v[j][k];
                B[k] = '\0';
                conv(A, B);
                long long sol = 0;
                int n = 0;
                for(int k = len - 1; k >= 0; k--) {
                    sol = sol + (A[k] * calc(n));
                    n++;
                }
                cout << '#' << i << ' ' << sol << '\n';
            }
        }
    }
    return 0;
}