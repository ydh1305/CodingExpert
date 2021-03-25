#include <stdio.h>

int M, K;
int sol[8][8];
int H[8], W[8], tH[8], tW[8], nH[8], nW[8];
int map[8][8], nmap[8][8];

int main(void) {
    int i, j;
    int cur, pos;
    scanf("%d %d", &M, &K);
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            scanf("%d", &map[i][j]);
            map[i][j] -= M;
            H[i] += map[i][j];
            W[j] += map[i][j];
        }
    }

    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            cur = H[i] + W[j] - map[i][j];
            if(cur % 2 == 1 || cur % 2 == -1){
                sol[i][j] = 1;
                tH[i]++; tW[j]++;
            }
        }
    }

    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            nmap[i][j] = tH[i] + tW[j] - sol[i][j];
            nH[i] += nmap[i][j];
            nW[j] += nmap[i][j];
        }
    }

    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            cur = nH[i] + nW[j] - nmap[i][j];
            if((H[i] + W[j] - map[i][j] - cur) % 4 == -2) sol[i][j] = -1; 
        }
    }

    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            if(sol[i][j] == 1) printf("+ ");
            else if(sol[i][j] == -1) printf("- ");
            else printf(". ");
        }
        printf("\n");
    }

    return 0;
}
