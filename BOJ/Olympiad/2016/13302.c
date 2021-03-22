#include <stdio.h>
#include <string.h>

int N, M;
int dp[101][101];
int off[101];

#define min(a,b) ((a>b)?(b):(a))
#define IMP (1 << 30)

int DFS(int n, int c){
    if(n > N) return 0;
    if(off[n]) return DFS(n + 1, c);
    if(dp[n][c] != -1) return dp[n][c];
    dp[n][c] = IMP;

    dp[n][c] = min(dp[n][c], DFS(n + 1, c) + 10000);
    dp[n][c] = min(dp[n][c], DFS(n + 3, c + 1) + 25000);
    dp[n][c] = min(dp[n][c], DFS(n + 5, c + 2) + 37000);

    if(c >= 3)
        dp[n][c] = min(dp[n][c], DFS(n + 1, c - 3));

    return dp[n][c];
}

int main(void){
    int i, x;
    scanf("%d %d", &N, &M);
    for(i = 0; i < M; i++){
        scanf("%d", &x);
        off[x] = 1;
    }
    memset(dp, -1, sizeof(dp));
    printf("%d\n", DFS(1, 0));

    return 0;
}
