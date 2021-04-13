#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

string s;
int len;

template <typename It>
void _swap(It &a, It &b) {
    It c(a); a = b; b = c;
}

void DFS(string str, int idx) {
    if(idx == len - 1) {
        cout << str << '\n';
        return;
    }
    for(int i = idx; i < len; i++) {
        if(i != idx && str[i] == str[idx]) continue;
        if(str[i] != str[idx]) {
            _swap(str[i], str[idx]);
        }
        DFS(str, idx + 1);
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int N; cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> s;
        len = s.length();
        sort(s.begin(), s.end());
        DFS(s, 0);
    }
    return 0;
}