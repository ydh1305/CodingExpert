#include <stdio.h>

int dp[100001];
int visit[100001];
int N, M;

int main(void) {
    int i;
    int x, y;
    scanf("%d %d", &N, &M);

    for(i = 1; i <= N; i++) dp[i] = i;
    for(i = 1; i <= M; i++){
        scanf("%d %d", &x, &y);
        dp[x]++; dp[y]--;
    }
    for(i = 1; i <= N; i++){
        if(!visit[dp[i]]){
            visit[dp[i]] = 1;
            continue;
        }
        printf("-1\n");
        return 0;
    }
    for(i = 1; i <= N; i++) printf("%d ", dp[i]);
    
    return 0;
}
