#include <iostream>
using namespace std;

#define MAX 51
#define INF (1<<30)
#define min(a,b) ((a>b)?(b):(a))

int N, M;
int map[MAX][MAX];
int sum[MAX][MAX];
int dp[MAX][MAX][MAX][MAX];

int DFS(int x1, int y1, int x2, int y2) {
    if(x1 == x2 && y1 == y2) return 0;
    if(dp[x1][y1][x2][y2] != -1) return dp[x1][y1][x2][y2];

    dp[x1][y1][x2][y2] = INF;
    int cur_sum = sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
    for(int i = x1; i < x2; i++) {
        int s1 = DFS(x1, y1, i, y2);
        int s2 = DFS(i + 1, y1, x2, y2);
        dp[x1][y1][x2][y2] = min(dp[x1][y1][x2][y2], s1 + s2 + cur_sum); 
    }
    for(int i = y1; i < y2; i++) {
        int s1 = DFS(x1, y1, x2, i);
        int s2 = DFS(x1, i + 1, x2, y2);
        dp[x1][y1][x2][y2] = min(dp[x1][y1][x2][y2], s1 + s2 + cur_sum);
    }
    return dp[x1][y1][x2][y2];
}

void get_totalsum() {
    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= M; j++)
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + map[i][j];
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N >> M;
        for(int j = 1; j <= N; j++)
            for(int k = 1; k <= M; k++)
                for(int h = 1; h <= N; h++)
                    for(int w = 1; w <= M; w++) dp[j][k][h][w] = -1;
        for(int j = 1; j <= N; j++)
            for(int k = 1; k <= M; k++) map[j][k] = 0;

        for(int j = 1; j <= N; j++)
            for(int k = 1; k <= M; k++) cin >> map[j][k]; 
        get_totalsum();
        cout << '#' << i << ' ' << DFS(1, 1, N, M) << '\n';
    }

    return 0;
}
