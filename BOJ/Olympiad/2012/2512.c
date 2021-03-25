#include <stdio.h>

int arr[10001];
int N, M;
int max;

int bs_search(int s, int e){
    int i, m, sol = 0;
    long long sum = 0;

    while(s <= e){
        m = (s + e) / 2;
        sum = 0;
        for(i = 0; i < N; i++){
            if(arr[i] > m) sum += m; 
            else sum += arr[i];
        }
        if(sum <= M){
           sol = m;
           s = m + 1;
        }
        else e = m - 1;
    }
    return sol;
}

int main(void){
    int i;
    scanf("%d", &N);
    for(i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
        if(max < arr[i]) max = arr[i];
    }
    scanf("%d", &M);
    printf("%d\n", bs_search(0, max));

    return 0;
}
