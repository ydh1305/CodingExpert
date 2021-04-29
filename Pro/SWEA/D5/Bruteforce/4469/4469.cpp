#include <bits/stdc++.h>
using namespace std;

int A[100001], B[100000];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int N; cin >> N;
        for(int j = 0; j < N; j++) cin >> A[j];
        for(int j = 0; j < N - 1; j++) cin >> B[j];
        
    }
    return 0;
}