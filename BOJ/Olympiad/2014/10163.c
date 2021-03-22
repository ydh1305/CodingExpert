#include <stdio.h>

int N;
int map[101][101];
int visit[101];

int main(void) {
    int i, j, k;
    int x, y, h, w;
    scanf("%d", &N);
    for(i = 1; i <= N; i++){
        scanf("%d %d %d %d", &x, &y, &w, &h);
        for(j = x; j < x + w; j++){
            for(k = y; k < y + h; k++){
                if(map[j][k]) visit[map[j][k]]--;
                map[j][k] = i;
                visit[map[j][k]]++;
            }
        }
    }
    for(i = 1; i <= N; i++) printf("%d\n", visit[i]);

    return 0;
}
