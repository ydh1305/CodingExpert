#include <bits/stdc++.h>
using namespace std;

int A[100001], B[100001];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        char s1[100001], s2[100001];
        int idx1 = 0, idx2 = 0;
        long long sum = 0;
        cin >> s1 >> s2;
        for(int j = 0; s1[j]; j++) {
            if(s1[j] == 'a') A[idx1++] = j;
            if(s2[j] == 'a') B[idx2++] = j;
        }
        for(int j = 0; j < idx1; j++) {
            sum = sum + abs(A[j] - B[j]);
        }
        cout << '#' << i << ' ' << sum << '\n';
    }
    return 0;
}