#include <iostream>
#include <cstring>
using namespace std;

char A[100001], B[100001];
int nA[100001], nB[100001];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> A >> B;
        int idx1 = 0, idx2 = 0;
        for(int i = 0; A[i]; ++i) {
            if(A[i] == 'a') nA[idx1++] = i;
            if(B[i] == 'a') nB[idx2++] = i;
        }
        long long sol = 0;
        for(int i = 0; i < idx1; ++i)
            sol = sol + abs(nA[i] - nB[i]);
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}