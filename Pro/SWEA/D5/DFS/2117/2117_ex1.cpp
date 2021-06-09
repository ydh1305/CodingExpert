#include <iostream>
using namespace std;

struct Data {
    int h;
    int w;
};
Data D[400];

int N, M, nD, sol;
int map[20][20];

bool check(int h, int w, int i, int k) {
    int dist = abs(h - D[i].h) + abs(w - D[i].w);
    if(k >= dist) return true;
    return false;
}

int DFS(int h, int w) {
    int sum = 0;
    for(int k = 1; k <= N + 1; ++k) {
        int num = 0;
        for(int i = 0; i < nD; ++i)
            if(check(h, w, i, k - 1)) num++;
        int K = k * k + ((k - 1) * (k - 1));
        if((num * M) - K >= 0)
            sum = max(sum, num);
    }
    return sum;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N >> M;
        nD = 0;
        for(int h = 0; h < N; ++h) {
            for(int w = 0; w < N; ++w) {
                cin >> map[h][w];
                if(map[h][w]) 
                    D[nD++] = { h, w };
            }
        }
        sol = 0;
        for(int h = 0; h < N; ++h) {
            for(int w = 0; w < N; ++w) {
                sol = max(sol, DFS(h, w));
            }
        }
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}