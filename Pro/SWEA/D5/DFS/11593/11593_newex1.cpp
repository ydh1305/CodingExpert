#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

char S[21];
char arr[26];
char pos[21];
int len, cnt;
long long sol;
long long f[21];

void DFS(int n) {
    if(n == len) return;
    int cur = S[n] - 'A';
    for(int i = 0; i < cnt; i++) {
        if(cur <= pos[i]) break;
        if(arr[pos[i]]) {
            arr[pos[i]]--;
            long long bot = 1;
            for(int j = 0; j < cnt; j++) {
                if(arr[pos[j]]) bot = bot * f[arr[pos[j]]];
            }
            long long top = f[len - (n + 1)];
            sol = sol + (top / bot);
            arr[pos[i]]++;
        }
    }
    arr[cur]--;
    DFS(n + 1);
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    f[0] = 1;
    for(int i = 1; i <= 20; i++)
        f[i] = f[i - 1] * i;
    int T; cin >> T;
    for(int t = 1; t <= T; t++) {
        cin >> S;
        len = strlen(S);
        cnt = 0;
        sol = 0;
        for(int i = 0; S[i]; i++) {
            int idx = S[i] - 'A';
            if(!arr[idx]) pos[cnt++] = idx; 
            arr[idx]++;
        }
        sort(pos, pos + cnt);
        DFS(0);
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}