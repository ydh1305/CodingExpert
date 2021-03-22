#include <stdio.h>

int N, M;
int arr[701][701];

int hh[3] = { 0, -1, -1 };
int ww[3] = { -1, -1, 0 };

int main(void){
    int i, j, x, y, z;
    int a, b, c;
    int max;

    scanf("%d %d", &N, &M);
    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            arr[i][j] = 1;

    for(i = 0; i < M; i++){
        scanf("%d %d %d", &a, &b, &c);

        for(j = N - 1; j > 0; j--){
            if(a) {
                a--;
                continue;
            }
            if(b) {
                arr[j][0] += 1; b--;
            }
            else if(c) {
                arr[j][0] += 2; c--;
            }
        }
        for(j = 0; j < N; j++){
            if(a) {
                a--;
                continue;
            }
            if(b) {
                arr[0][j] += 1; b--;
            }
            else if(c) {
                arr[0][j] += 2; c--;
            }
        }
    }
    for(y = 1; y < N; y++){
        for(x = 1; x < N; x++){
            max = -1;
            for(z = 0; z < 3; z++){
                if(max < arr[y + hh[z]][x + ww[z]])
                    max = arr[y + hh[z]][x + ww[z]];
            }
            arr[y][x] = max;
        }
    }
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}
