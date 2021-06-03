#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> v;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int N; cin >> N;
        v.clear();
        char s1[401]; cin >> s1;
        char s2[401];
        int len = strlen(s1);
        v.push_back(s1);
        for(int i = 1; i < len; ++i) {
            strcpy(s2, s1 + i);
            v.push_back(s2);
        }
        sort(v.begin(), v.end());
        cout << '#' << t << ' ' << v[N - 1] << '\n';
    }
    return 0;
}