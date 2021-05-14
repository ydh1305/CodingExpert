#include <bits/stdc++.h>
using namespace std;

#define HASH_SIZE 28
#define PN 23

int N, K, sol;
int dp[8];

struct HashMap {
    char name[HASH_SIZE][8];
    int hash_table[HASH_SIZE][5];
    int name_idx;

    void clear(void) {
        name_idx = 0;
        for(int i = 0; i < HASH_SIZE; i++)
            hash_table[i][0] = 0;
    }
    unsigned int get_key(char *str) {
        unsigned int key = 0, p = 1;
        for(int i = 0; str[i]; i++) {
            key = key + (str[i] * p);
            p = p * PN;
        }
        return key % HASH_SIZE;
    }
    int _strcmp(char *a, char *b) {
        int i = 0;
        while(a[i]) {
            if(a[i] != b[i]) break;
            i++;
        }
        return a[i] - b[i];
    }
    int contain(char *str) {
        unsigned int key = get_key(str);
        int h_size = hash_table[key][0];
        for(int i = 1; i <= h_size; i++) {
            int pos = hash_table[key][i];
            if(_strcmp(str, name[pos]) == 0)
                return pos;
        }
        return -1;
    }
    int insert(char *str) {
        int i = 0;
        for(; str[i]; i++)
            name[name_idx][i] = str[i];
        name[name_idx][i] = '\0';

        unsigned int key = get_key(str);
        int& h_size = hash_table[key][0];
        hash_table[key][++h_size] = name_idx;

        ++name_idx;
        return name_idx - 1;
    }
    int cal(int cnt) {
        if(dp[cnt]) return dp[cnt];
        if(cnt == 0) {
            dp[cnt] = 1;
        } else {
            dp[cnt] = dp[cnt - 1] * 16;
        }
        return dp[cnt];
    }
    void conv(int *S, char *C) {
        for(int i = 0; C[i]; i++) {
            if(C[i] >= 'A') S[i] = C[i] - 'A' + 10;
            else S[i] = C[i] - '0';
        }
    }
    void search(void) {
        vector<string> v;
        for(int i = 0; i < name_idx; i++)
            v.push_back(name[i]);
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
        for(i = len - 1; i >= 0; i--) {
            sol = sol + S[i] * cal(k++);
        }
    }
};
HashMap hm;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; t++) {
        cin >> N >> K;
        int d = N / 4;
        char str[29]; cin >> str;
        char tmp[8];
        hm.clear();
        int it;
        for(int i = 0; i < N; i++) {
            int s = i, idx = 0;
            for(int j = 0; j < d; j++) {
                if(s == N) s = 0;
                tmp[idx++] = str[s++];
            }
            tmp[idx] = '\0';
            it = hm.contain(tmp);
            if(it == -1) hm.insert(tmp);
        }
        hm.search();
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}