#include <bits/stdc++.h>
using namespace std;

string s;
int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int N; cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> s;
        sort(s.begin(), s.end());
        do {
            cout << s << '\n';
        } while(next_permutation(s.begin(), s.end()));
    }
    return 0;
}