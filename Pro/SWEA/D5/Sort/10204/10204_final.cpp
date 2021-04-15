#include <bits/stdc++.h>
using namespace std;

#define MAX 100001

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cin.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int N; cin >> N;
        int arr[MAX];
        long long sol = 0;
        for(register int j = 0; j < N; j++) {
            int a, b; cin >> a >> b;
            arr[j] = a + b;
            sol = sol - b;
        }
        sort(arr, arr + N);
        for(int j = N - 1; j >= 0; j = j - 2)
            sol = sol + arr[j];
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}