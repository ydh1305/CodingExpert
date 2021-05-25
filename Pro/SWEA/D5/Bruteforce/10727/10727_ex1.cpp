#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int H[200001], W[200001];
int visit[10000001];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int N, M, Q; cin >> N >> M >> Q;
        int sum = 0;
        long long sol = 0;
        memset(visit, 0, sizeof(visit));
        for(int h = 1; h <= N; ++h) {
            H[h] = 0;
            for(int w = 1; w <= M; ++w) {
                int x; cin >> x;
                if(h == 1) W[w] = 0;
                H[h] = max(H[h], x);
                W[w] = max(W[w], x);
                if(h == N) {
                    visit[W[w]]++;
                    if(visit[W[w]] == 2) sum = sum + 1;
                }
            }
            visit[H[h]]++;
            if(visit[H[h]] == 2) sum = sum + 1;
        }
        for(int i = 0; i < Q; ++i) {
            int r, c, x; cin >> r >> c >> x;
            if(H[r] < x) {
                if(visit[H[r]] == 2) sum = sum - 1;
                visit[H[r]]--;
                H[r] = x;
                visit[H[r]]++;
                if(visit[H[r]] == 2) sum = sum + 1;
            }
            if(W[c] < x) {
                if(visit[W[c]] == 2) sum = sum - 1;
                visit[W[c]]--;
                W[c] = x;
                visit[W[c]]++;
                if(visit[W[c]] == 2) sum = sum + 1;
            } 
            sol = sol + sum;
        }
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}