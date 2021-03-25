#include <stdio.h>
#include <stdlib.h>

struct box {
    int s;
    int e;
    int c;
};
struct box B[10001];

int N, C, M;
int capa[2001];

#define min(a,b) ((a>b)?(b):(a))

int compare(void const *a, void const *b){
    struct box *m = (struct box *)a;
    struct box *n = (struct box *)b;
    if(m->e > n->e) return 1;
    else if(m->e < n->e) return -1;
    else {
        if(m->s > n->s) return 1;
        else if(m->s < n->s) return -1;
        else return 0;
    }
}

int main(void){
    int i, j;
    int spare;
    int sum = 0;

    scanf("%d %d %d", &N, &C, &M);
    for(i = 0; i < M; i++) scanf("%d %d %d", &B[i].s, &B[i].e, &B[i].c); 
    qsort(B, M, sizeof(struct box), compare);
    for(i = 1; i <= N; i++) capa[i] = C; 

    for(i = 0; i < M; i++){
        spare = C;
        for(j = B[i].s; j < B[i].e; j++) spare = min(spare, capa[j]);

        if(B[i].c > spare) B[i].c = spare;
        sum += B[i].c;
        for(j = B[i].s; j < B[i].e; j++) capa[j] -= B[i].c;
    }
    printf("%d\n", sum);

    return 0;
}
