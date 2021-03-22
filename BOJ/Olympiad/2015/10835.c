#include <stdio.h>
#include <string.h>

int N;
int A[2001], B[2001];
int dp[2001][2001];

#define max(a,b) ((a>b)?(a):(b))

int DFS(int l, int r){
    if(l == N || r == N) return 0;
    if(dp[l][r] != -1) return dp[l][r];

    dp[l][r] = max(dp[l][r], DFS(l + 1, r));
    dp[l][r] = max(dp[l][r], DFS(l + 1, r + 1));
    if(A[l] > B[r])
        dp[l][r] = max(dp[l][r], DFS(l, r + 1) + B[r]);
    return dp[l][r];
}

int main(void){
    int i;
    scanf("%d", &N);
    for(i = 0; i < N; i++) scanf("%d", &A[i]);
    for(i = 0; i < N; i++) scanf("%d", &B[i]);
    memset(dp, -1, sizeof(dp));
    printf("%d\n", DFS(0, 0));

    return 0;
}
