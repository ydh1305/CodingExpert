#include <stdio.h>
#include <stdlib.h>

struct data {
    int p;
    int s;
};
struct data D[30001];

int N, K, S;

int compare(void const *a, void const *b){
    struct data *m = (struct data *)a;
    struct data *n = (struct data *)b;
    if(m->p > n->p) return 1;
    else if(m->p < n->p) return -1;
    else return 0;
}

int main(void) {
    int i, j;
    int idx = 0;
    int bus = 0;
    int sum = 0;
    scanf("%d %d %d", &N, &K, &S);
    for(i = 0; i < N; i++) scanf("%d %d", &D[i].p, &D[i].s);
    D[N].p = S; D[N].s = 0;
    qsort(D, N + 1, sizeof(struct data), compare);
    for(i = 0; i <= N; i++) if(D[i].p == S) idx = i;

    for(i = 0; i < idx; i++){
        bus = 0;
        for(j = i; j < idx; j++){
            bus += D[j].s;
            if(bus > K) {
                D[j].s = bus - K;
                break;
            }
        }
        sum += (S - D[i].p) * 2; 
        i = --j;
    }

    for(i = N; i > idx; i--){
        bus = 0;
        for(j = i; j > idx; j--){
            bus += D[j].s;
            if(bus > K) {
                D[j].s = bus - K;
                break;
            }
        }
        sum += (D[i].p - S) * 2;
        i = +j;
    }
    printf("%d\n", sum);

    return 0;
}
