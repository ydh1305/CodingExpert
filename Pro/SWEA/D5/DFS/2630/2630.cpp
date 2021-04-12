#include <iostream>
using namespace std;

#define MAX 130
int map[MAX][MAX];
int color[2];

void DFS(int n, int x1, int y1, int x2, int y2) {
    int cur = map[x1][y1];
    int m = n / 2;
    for(int h = x1; h < x2; h++) {
        for(int w = y1; w < y2; w++) {
            if(cur != map[h][w]) {
                DFS(m, x1, y1, x2 - m, y2 - m);
                DFS(m, x1 + m, y1 + m, x2, y2);
                DFS(m, x1 + m, y1, x2, y2 - m);
                DFS(m, x1, y1 + m, x2 - m, y2);
                return;
            }
        }
    }
    color[cur]++;
    return;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int N; cin >> N;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            cin >> map[i][j];
    DFS(N, 0, 0, N, N);
    cout << color[0] << '\n';
    cout << color[1] << '\n';

    return 0;
}