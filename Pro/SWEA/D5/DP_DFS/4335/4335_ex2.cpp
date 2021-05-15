#include <iostream>
using namespace std;

int box[20][3];
int dp[1 << 20][20][3];
int N;

int DFS(int bit, int n, int stat, int h, int w) {
    int& sol = dp[bit][n][stat];
    if(sol != -1) return sol;
    sol = 0;
    for(int i = 0; i < N; i++) {
        if(bit & (1 << i)) continue;
        if((h <= box[i][0] && w <= box[i][1]) || (h <= box[i][1] && w <= box[i][0]))
            sol = max(sol, box[i][2] + DFS(bit | (1 << i), i, 0, box[i][0], box[i][1]));
        if((h <= box[i][1] && w <= box[i][2]) || (h <= box[i][2] && w <= box[i][1]))
            sol = max(sol, box[i][0] + DFS(bit | (1 << i), i, 1, box[i][1], box[i][2]));
        if((h <= box[i][0] && w <= box[i][2]) || (h <= box[i][2] && w <= box[i][0]))
            sol = max(sol, box[i][1] + DFS(bit | (1 << i), i, 2, box[i][0], box[i][2]));           
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; t++) {
        cin >> N;
        for(int i = 0; i < N; i++)
            cin >> box[i][0] >> box[i][1] >> box[i][2];
        for(int i = 0; i < (1 << N); i++)
            for(int j = 0; j < N; j++)
                dp[i][j][0] = dp[i][j][1] = dp[i][j][2] = -1;
        cout << '#' << t << ' ' << DFS(0, 0, 0, 0, 0) << '\n';
    }
    return 0;
}