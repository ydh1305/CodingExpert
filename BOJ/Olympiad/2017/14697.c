#include <stdio.h>

int main(void){
    int A, B, C, S;
    int i, j, k, z;
    scanf("%d %d %d %d", &A, &B, &C, &S);
    for(i = 0; i <= S / A; i++){
        for(j = 0; j <= S / B; j++){
            for(k = 0; k <= S / C; k++){
                if(A*i+B*j+C*k == S) {
                    printf("1\n");
                    return 0;
                }
            }
        }
    }
    printf("0\n");
    return 0;
}
