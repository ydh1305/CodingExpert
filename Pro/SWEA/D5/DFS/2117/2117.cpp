#include <iostream>
using namespace std;

struct data {
    int h;
    int w;
};
struct data H[400];
int nH, sol;
int N, M;

bool check(int h, int w, int m, int k) {
    int dist = abs(h - H[m].h) + abs(w - H[m].w);
    if(k >= dist) return true;
    return false;
}

int DFS(int h, int w) {
    int sum = 0;
    for(int k = 1; k <= N + 1; k++) {
        int num = 0;
        for(int i = 0; i < nH; i++) {
            if(!check(h, w, i, k - 1)) continue;
            num++;
        }
        int K = k * k + (k - 1) * (k - 1);
        if((num * M) - K >= 0) sum = num;
    }
    return sum;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N >> M;
        nH = 0;
        for(int h = 0; h < N; h++) {
            for(int w = 0; w < N; w++) {
                int x; cin >> x;
                if(x == 1) H[nH++] = { h, w };
            }
        }
        sol = 0;
        for(int h = 0; h < N; h++) {
            for(int w = 0; w < N; w++) {
                sol = max(sol, DFS(h, w));
            }
        }
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}