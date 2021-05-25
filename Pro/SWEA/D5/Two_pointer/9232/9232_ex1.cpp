#include <iostream>
using namespace std;

int arr[300001];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int N, Q; cin >> N >> Q;
        int limit = 1000000001;
        int x;
        for(int i = 1; i <= N; ++i) {
            cin >> x;
            limit = min(limit, x);
            arr[i] = limit;
        }
        int e = N;
        for(int s = 1; s <= Q; ++s) {
            cin >> x;
            while(arr[e] < x && e >= 1) e--;
            if(e <= 0) continue;
            if(s < Q) e--;
        }
        cout << '#' << t << ' ' << e << '\n';
    }
    return 0;
}