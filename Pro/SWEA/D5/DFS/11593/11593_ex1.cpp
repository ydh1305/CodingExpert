#include <bits/stdc++.h>
using namespace std;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int N; cin >> N;
    for(int i = 1; i <= N; i++) {
        char s1[21]; cin >> s1;
        char s2[21];
        int total = 0;
        strcpy(s2, s1);
        sort(s2, s2 + strlen(s2));
        do {
            if(strcmp(s1, s2) <= 0) break;
            total++;
        } while(next_permutation(s2, s2 + strlen(s2)));
        cout << '#' << i << ' ' << total << '\n';
    }
    return 0;
}