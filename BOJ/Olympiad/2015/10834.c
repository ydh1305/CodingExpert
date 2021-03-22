#include <stdio.h>

struct belt {
    int a;
    int b;
    int d;
};
struct belt B[1001];
int M;

int main(void){
    int i;
    int d, r, w;
    scanf("%d", &M);
    for(i = 0; i < M; i++) scanf("%d %d %d", &B[i].a, &B[i].b, &B[i].d);
    d = B[0].b / B[0].a; w ^= B[0].d;
    for(i = 1; i < M; i++) {
        r = d / B[i].a;
        B[i].b = B[i].b * r;
        d = B[i].b;
        w ^= B[i].d; 
    }
    printf("%d %d\n", w, d);

    return 0;
}
