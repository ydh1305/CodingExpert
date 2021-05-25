#include <iostream>
#include <algorithm>
using namespace std;

int arr[100000];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; t++) {
        int N; cin >> N;
        long long sol = 0;
        for(int i = 0; i < N; i++) {
            int a, b; cin >> a >> b;
            arr[i] = a + b;
            sol = sol - b;
        }
        sort(arr, arr + N);
        for(int i = N - 1; i >= 0; i = i - 2)
            sol = sol + arr[i];
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}