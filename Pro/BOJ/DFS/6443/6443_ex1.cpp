#include <bits/stdc++.h>
using namespace std;

string s;
int arr[26];

void DFS(int n, string str) {
    if(n == s.length()) {
        cout << str << '\n';
        return;
    }
    for(int i = 0; i < 26; i++) {
        if(arr[i]) {
            arr[i]--;
            str[n] = i + 'a';
            DFS(n + 1, str);
            arr[i]++;
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int N; cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> s;
        memset(arr, 0, sizeof(arr));
        for(int j = 0; s[j]; j++) {
            int cur = s[j] - 'a';
            arr[cur]++;
        }
        DFS(0, s);
    }
    return 0;
}