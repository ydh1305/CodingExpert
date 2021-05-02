#include<iostream>
 
using namespace std;
 
int dp[21][1 << 20][3];
int cube[21][3];
int n;
  
int dfs(int r, int c, int now, int mode, int visit)
{
    int &nn = dp[now][visit][mode];
    if (nn) return nn;
     
 
    for (int i = 1; i <= n; i++)
    {
        if (visit & 1 << (i-1)) continue;
        int rc = visit | 1 << (i-1);
        if ((r <= cube[i][0] && c <= cube[i][1]) || (r <= cube[i][1] && c <= cube[i][0]))
            nn = max(nn, cube[i][2] + dfs(cube[i][0], cube[i][1], i, 0, rc));
        if ((r <= cube[i][0] && c <= cube[i][2]) || (r <= cube[i][2] && c <= cube[i][0]))
            nn = max(nn, cube[i][1] + dfs(cube[i][0], cube[i][2], i, 1, rc));
        if ((r <= cube[i][2] && c <= cube[i][1]) || (r <= cube[i][1] && c <= cube[i][2]))
            nn = max(nn, cube[i][0] + dfs(cube[i][2], cube[i][1], i, 2, rc));
    }
    return nn;
}

int main()
{
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        cin >> n;
 
        for (int i = 0; i <= n; i++)
            for (int j = 0; j < (1 << (n)); j++)
                for (int k = 0; k < 3; k++)
                    dp[i][j][k] = 0;
 
 
        for (int i = 1;i <= n; i++)
            cin >> cube[i][0] >> cube[i][1] >> cube[i][2];
 
 
 
        cout << '#' << tc << ' ' << dfs(0, 0, 0, 0, 0) << endl;
 
 
 
    }
    return 0;
}