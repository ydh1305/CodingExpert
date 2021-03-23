#include <stdio.h>
#include <stdlib.h>

struct bus {
    int i;
    int s;
    int e;
};
struct bus C[500001], R[500001];

int S[500001];
int N, M;
int C_cnt, R_cnt;

int compare(void const *a, void const *b){
    struct bus *m = (struct bus *)a;
    struct bus *n = (struct bus *)b;
    if(m->s > n->s) return 1;
    else if(m->s < n->s) return -1;
    else {
        if(m->e < n->e) return 1;
        else if(m->e > n->e) return -1;
        else return 0;
    }
}

int main(void){
    int i;
    int x, y;
    int r_min = 1 << 30, r_max = 0;
    int limit = 0;
    scanf("%d %d", &N, &M);

    for(i = 0; i < M; i++){
        scanf("%d %d", &x, &y);
        if(x < y) C[C_cnt].s = x, C[C_cnt].e = y, C[C_cnt++].i = i + 1; 
        else {
            if(r_max < y) r_max = y; if(r_min > x) r_min = x;
            R[R_cnt].s = x, R[R_cnt].e = y, R[R_cnt++].i = i + 1;
        }
    }
    qsort(C, C_cnt, sizeof(struct bus), compare);
    qsort(R, R_cnt, sizeof(struct bus), compare);

    for(i = 0; i < C_cnt; i++){
        if(C[i].s >= r_min) S[C[i].i] = 1;
        if(C[i].e <= r_max) S[C[i].i] = 1;
        if(C[i].e <= limit) S[C[i].i] = 1;
        else limit = C[i].e;
    }

    limit = -1;
    for(i = 0; i < R_cnt; i++){
        if(R[i].e <= limit) S[R[i].i] = 1;
        else limit = R[i].e;
    }

    for(i = 1; i <= M; i++) if(!S[i]) printf("%d ", i);

    return 0;
}
