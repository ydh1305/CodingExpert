#include <stdio.h>

struct data {
    int b;
    int a;
};
struct data D[40001];

int N, K;
int H[2501];

#define min(a,b) ((a>b)?(b):(a))
#define max(a,b) ((a>b)?(a):(b))

int main(void){
    int x1, x2, y1, y2;
    int i, j;
    int high;
    int max_x;
    int sum = 0;
    scanf("%d", &N);
    scanf("%d %d", &x1, &x2);
    for(i = 0; i < (N / 2) - 1; i++){
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        for(j = x1; j < x2; j++) D[j].b = y1;
    }
    scanf("%d %d", &x1, &x2);
    max_x = x1;
    scanf("%d", &K);
    for(i = 0; i < K; i++){
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        H[i] = x1;
    }

    for(i = 0; i < K; i++){
        high = D[H[i]].b;
        D[H[i]].a = high;
        for(j = H[i] - 1; j >= 0; j--){
            high = min(high, D[j].b);
            D[j].a = max(high, D[j].a);
        }

        high = D[H[i]].b;
        for(j = H[i] + 1; j < max_x; j++){
            high = min(high, D[j].b);
            D[j].a = max(high, D[j].a);
        }
    }

    for(i = 0; i < max_x; i++) sum += (D[i].b - D[i].a);
    printf("%d\n", sum);

    return 0;
}
