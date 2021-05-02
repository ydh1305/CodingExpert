#include <stdio.h>
 
int T, N, map[50][50];
int res;
int chk[50][50][4];// 해당 방향으로 들어왔을 때 최단 거리
int chk2[50][50] = { 0 };
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
 
void dfs(int x, int y, int in, int len, int num)
{
    int X, Y;
    printf("[%d][%d] in = %d len = %d\n", x, y, in, len);
    for (int d = 0; d < 4; d++)
    {
        if (map[x][y] == 1 || map[x][y] == 2) // in == out
            if (in != d) continue;
        if (map[x][y] >= 3 && map[x][y] <= 6)
        {
            if (in == 0 || in == 2)
                if (d != 1 && d != 3) continue;
            if (in == 1 || in == 3)
                if (d != 0 && d != 2) continue;
        }
        X = x + dx[d];
        Y = y + dy[d];
        //종료 조건
        if (num == 0 && X == N - 1 && Y == N && res > len)
        {
            res = len;
            continue;
        }
        if (num == 1 && X == 0 && Y == -1 && res > len)
        {
            res = len;
            continue;
        }
        if (X < 0 || Y < 0 || X >= N || Y >= N || map[X][Y] == 0 || chk2[X][Y] == 1)
            continue;
        if (chk[X][Y][d] < len + 1)
            continue;
        chk[X][Y][d] = len + 1;
        chk2[X][Y] = 1;
        dfs(X, Y, d, len + 1, num);
        chk2[X][Y] = 0;
    }
}
int main() {
    scanf("%d", &T);
    for (int t = 1; t <= T; t++)
    {
        res = 999;
        scanf("%d", &N);
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                for (int d = 0; d < 4; d++)
                    chk[i][j][d] = 999;
                scanf("%d", &map[i][j]);
            }
        }
        chk[0][0][0] = 1;
        dfs(0, 0, 0, 1, 0);
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                for (int d = 0; d < 4; d++)
                    chk[i][j][d] = 999;
            }
        }
        chk[N-1][N-1][2] = 1;
        dfs(N - 1, N - 1, 2, 1, 1);
        printf("#%d %d\n", t, res);
    }
    return 0;
}