#include <iostream>
using namespace std;

int arr[10001];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; t++) {
        int N, M; cin >> N >> M;
        for(int i = 1; i <= N; i++)
            arr[i] = N - 1;
        for(int i = 0; i < M; i++) {
            int a, b; cin >> a >> b;
            arr[a]--; arr[b]--;
        }
        int sol = 10000;
        for(int i = 1; i <= N; i++) {
            if(sol > arr[i]) sol = arr[i];
        }
        cout << '#' << t << ' ' << sol - 1 << '\n';
    }
    return 0;
}