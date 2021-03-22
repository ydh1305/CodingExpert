#include <stdio.h>

int N, M, K;

int DFS(int y, int x){
    if(y < 1 || x < 1) return 0;
    if(y == 1 && x == 1) return 1;
    return DFS(y - 1, x) + DFS(y, x - 1);
}

int main(void) {
    int i, j, h, w;
    int num = 1;
    scanf("%d %d %d", &N, &M, &K);
    for(i = 1; i <= N; i++){
        for(j = 1; j <= M; j++){
            if(K == num++) h = i, w = j; 
        }
    }

    if(!K) printf("%d\n", DFS(N, M));
    else printf("%d\n", DFS(h, w) * DFS(N - h + 1, M - w + 1));

    return 0;
}
