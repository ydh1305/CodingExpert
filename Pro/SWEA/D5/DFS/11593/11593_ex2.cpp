#include <bits/stdc++.h>
using namespace std;

int arr[26];
char str[21];
char tmp[21];
int len, total;

void DFS(int n) {
    if(n == strlen(str)) {
        if(strncmp(str, tmp, strlen(tmp)) <= 0) return;
        total++;
        return;
    }
    for(int i = 0; i < 26; i++) {
        if(arr[i]) {
            arr[i]--;
            tmp[n] = i + 'A';
            if(strncmp(str, tmp, strlen(tmp) < 0)) continue;      
            DFS(n + 1);
            arr[i]++;
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int N; cin >> N;
    for(int i = 1; i <= N; i++) {
        total = 0;
        memset(str, 0, sizeof(str));
        memset(tmp, 0, sizeof(tmp));
        memset(arr, 0, sizeof(arr));
        cin >> str;
        for(int j = 0; str[j]; j++) arr[str[j] - 'A']++;
        DFS(0);
        cout << '#' << i << ' ' << total << '\n';
    }
    return 0;
}