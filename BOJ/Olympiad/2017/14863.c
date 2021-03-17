#include <stdio.h>

struct data {
    int t;
    int m;
};
struct data W[101], B[101]; 
int N, K;
int dp[101][100001];

#define max(a,b) ((a>b)?(a):(b))

int DFS(int n, int time) {
    if(n == N) return 0;
    if(dp[n][time]) return dp[n][time];
    dp[n][time] = -987654321;

    if(time + W[n].t <= K)
        dp[n][time] = max(dp[n][time], DFS(n + 1, time + W[n].t) + W[n].m);
    if(time + B[n].t <= K)
        dp[n][time] = max(dp[n][time], DFS(n + 1, time + B[n].t) + B[n].m);

    return dp[n][time];
}

int main(void) {
    int i;
    scanf("%d %d", &N, &K);
    for(i = 0; i < N; i++)
        scanf("%d %d %d %d", &W[i].t, &W[i].m, &B[i].t, &B[i].m);
    printf("%d\n", DFS(0, 0));

    return 0;
}
