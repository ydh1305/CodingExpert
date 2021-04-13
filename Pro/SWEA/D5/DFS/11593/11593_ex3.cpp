#include <bits/stdc++.h>
using namespace std;

string s;
string s1;
int len;
int total;

void DFS(string str, int idx) {
    if(idx == len - 1) {
        total++;
        return;
    }
    for(int i = idx; i < len; i++) {
        if(i != idx && str[i] == str[idx]) continue;
        
        if(str[i] != str[idx]) {
            swap(str[i], str[idx]);
        }
        if(s1.compare(str) <= 0) return;
        cout << str << '\n';
        DFS(str, idx + 1);
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> s;
        s1 = s;
        total = 0;
        len = s.length();
        sort(s.begin(), s.end());
        DFS(s, 0);
        cout << '#' << i << ' ' << total << '\n';
    }
    return 0;
}