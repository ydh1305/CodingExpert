#include <bits/stdc++.h>
using namespace std;

const int MAX = 200000;
int H[MAX + 1], W[MAX + 1];
int visit[10000001];
int N, M, Q;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N >> M >> Q;
        long long total = 0;
        long long sum = 0;
        memset(visit, 0, sizeof(visit));
        for(int h = 1; h <= N; h++) {
            H[h] = 0;
            for(int w = 1; w <= M; w++) {
                if(h == 1) W[w] = 0;
                int x; cin >> x;
                H[h] = max(H[h], x);
                W[w] = max(W[w], x);
                if(h == N) {
                    visit[W[w]]++;
                    if(visit[W[w]] == 2) sum++;
                }
            }
            visit[H[h]]++;
            if(visit[H[h]] == 2) sum++;
        }
        for(register int j = 0; j < Q; j++) {
            int r, c, x; cin >> r >> c >> x;  
            if(H[r] < x) {
                if(visit[H[r]] == 2) sum--;
                visit[H[r]]--;
                H[r] = x;
                visit[H[r]]++;
                if(visit[H[r]] == 2) sum++;
            }
            if(W[c] < x) {
                if(visit[W[c]] == 2) sum--;
                visit[W[c]]--;
                W[c] = x;
                visit[W[c]]++;
                if(visit[W[c]] == 2) sum++;
            }
            total = total + sum;
        }
        printf("#%d %lld\n", i, total);
    }
    return 0;
}