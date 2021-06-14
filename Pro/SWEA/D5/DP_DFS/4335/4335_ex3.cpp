#include <iostream>
using namespace std;

struct Box {
    int x;
    int y;
    int z;
};
Box box[20];

int N, e;
int dp[1 << 20][20][3];

int DFS(int bit, int n, int x, int y, int stat) {
    if(bit == e - 1) return 0;
    int& sol = dp[bit][n][stat];
    if(sol != -1) return sol;
    sol = 0;
    for(int i = 0; i < N; ++i) {
        if(bit & (1 << i)) continue;
        if((x <= box[i].x && y <= box[i].y) || (x <= box[i].y && y <= box[i].x))
            sol = max(sol, box[i].z + DFS(bit | (1 << i), i, box[i].x, box[i].y, 0));
        if((x <= box[i].y && y <= box[i].z) || (x <= box[i].z && y <= box[i].y))
            sol = max(sol, box[i].x + DFS(bit | (1 << i), i, box[i].y, box[i].z, 1));
        if((x <= box[i].x && y <= box[i].z) || (x <= box[i].z && y <= box[i].x))
            sol = max(sol, box[i].y + DFS(bit | (1 << i), i, box[i].x, box[i].z, 2));
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N;
        for(int i = 0; i < N; ++i)
            cin >> box[i].x >> box[i].y >> box[i].z;
        for(int i = 0; i < (1 << N); ++i)
            for(int j = 0; j < N; ++j)
            dp[i][j][0] = dp[i][j][1] = dp[i][j][2] = -1;
        e = e | (1 << N);
        cout << '#' << t << ' ' << DFS(0, 0, 0, 0, 0) << '\n';
    }
    return 0;
}