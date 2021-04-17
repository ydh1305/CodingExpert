#include <iostream>
using namespace std;

const int MAX = 300000;
int H[MAX + 1], M[MAX + 1];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int N, Q; cin >> N >> Q;
        int limit = (1 << 30);
        for(int j = 1; j <= N; j++) {
            cin >> H[j];
            limit = min(limit, H[j]);
            M[j] = limit;
        }
        register int e = N;
        for(int s = 1; s <= Q; s++) {
            int x; cin >> x;
            while(M[e] < x && e >= 1) e--;
            if(e <= 0) continue;
            if(s < Q) e--;
        }
        cout << '#' << i << ' ' << e << '\n';
    }
    return 0;
}