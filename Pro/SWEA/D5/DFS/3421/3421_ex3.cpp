#include <iostream>
using namespace std;

int N, M, sol;
int check[21];
bool visit[21];

void DFS(int n, int bit) {
    sol++;
    for(int i = n; i <= N; ++i) {
        if(visit[i]) continue;
        if(check[i] & bit) continue;
        visit[i] = true;
        DFS(i + 1, bit | (1 << i));
        visit[i] = false;
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; t++) {
        cin >> N >> M;
        for(int i = 1; i <= N; ++i)
            check[i] = 0;
        for(int i = 0; i < M; ++i) {
            int a, b; cin >> a >> b;
            check[a] = check[a] | (1 << b);
            check[b] = check[b] | (1 << a);
        }
        sol = 0;
        DFS(1, 0);
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}