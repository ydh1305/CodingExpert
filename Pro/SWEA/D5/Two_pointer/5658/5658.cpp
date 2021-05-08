#include <bits/stdc++.h>
using namespace std;

char str[29];
char temp[8];
int N, K;
int dp[8];
vector<string> v;

#define HASH_SIZE 30
#define PN 23

struct HashMap {
    char name[HASH_SIZE][8];
    int hash_table[HASH_SIZE][10];
    int name_idx;

    void clear() {
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

        name_idx++;
        return name_idx - 1;
    }
    void conv(int *s, char *c) {
        int num = 0;
        for(int i = 0; c[i]; i++) {
            if(c[i] >= 'A') num = c[i] - 'A' + 10;
            else num = c[i] - '0';
            s[i] = num;
        }
    }
    long long calc(int cnt) {
        long long num = 1;
        if(cnt == 0) return 1;
        if(dp[cnt]) return dp[cnt];
        for(int i = 1; i <= cnt; i++) {
            num = num * 16;
        }
        dp[cnt] = num;
        return dp[cnt];
    }
    void solve(void) {
        for(int i = 0; i < name_idx; i++)
            v.push_back(name[i]);
        sort(v.begin(), v.end(), greater<string>());
        for(int i = 0; i < v.size(); i++) {
            if(i == K - 1) {
                int s[8];
                char c[8];
                int j = 0;
                int len = v[i].length();
                for(; j < len; j++)
                    c[j] = v[i][j];
                c[j] = '\0';
                conv(s, c);
                long long sol = 0;
                int n = 0;
                for(int j = len - 1; j >= 0; j--) {
                    sol = sol + s[j] * calc(n);
                    n++;
                }
                cout << sol << '\n';
            }
        }
    }
};
HashMap hm;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N >> K;
        cin >> str;
        int s = 0, e = 0;
        int d = N / 4;
        hm.clear();
        v.clear();
        while(s <= N - 1) {
            int idx = 0;
            e = s;
            for(int i = 1; i <= d; i++) {
                if(e == N) e = 0;
                temp[idx++] = str[e++];
            }
            temp[idx] = '\0';
            if(hm.contain(temp) == -1) hm.insert(temp);
            s++;
        }
        cout << '#' << i << ' ';
        hm.solve();
    }
    return 0;
}