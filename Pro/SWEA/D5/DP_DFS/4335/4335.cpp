#include <iostream>
using namespace std;

int dp[1 << 20][21][3];
int box[21][3];
int N;

int DFS(int bit, int cur, int com, int x, int y) {
    int& sol = dp[bit][cur][com];
    if(sol != -1) return sol;
    sol = 0;
    for(int i = 0; i < N; i++) {
        if(bit & (1 << i)) continue;
        if((x <= box[i][0] && y <= box[i][1]) || (x <= box[i][1] && y <= box[i][0]))
            sol = max(sol, box[i][2] + DFS(bit | (1 << i), i, 0, box[i][0], box[i][1]));
        if((x <= box[i][1] && y <= box[i][2]) || (x <= box[i][2] && y <= box[i][1]))
            sol = max(sol, box[i][0] + DFS(bit | (1 << i), i, 2, box[i][1], box[i][2]));
        if((x <= box[i][2] && y <= box[i][0]) || (x <= box[i][0] && y <= box[i][2]))
            sol = max(sol, box[i][1] + DFS(bit | (1 << i), i, 1, box[i][2], box[i][0]));
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N;
        for(int j = 0; j < N; j++)
            cin >> box[j][0] >> box[j][1] >> box[j][2];
        for(int a = 0; a < (1 << N); a++)
            for(int b = 0; b < N; b++)
                for(int c = 0; c < 3; c++)
                    dp[a][b][c] = -1;
        cout << '#' << i << ' ' << DFS(0, 0, 0, 0, 0) <<'\n';
    }
    return 0;
}