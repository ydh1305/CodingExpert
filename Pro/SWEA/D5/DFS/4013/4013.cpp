#include <iostream>
using namespace std;

int D[5][8];
int R[5];

int rotate(int idx, int dir) {
    if(dir == 1) {
        int temp = D[idx][7];
        for(int i = 6; i >= 0; i--)
            D[idx][i + 1] = D[idx][i];
        D[idx][0] = temp;
    }
    else {
        int temp = D[idx][0];
        for(int i = 1; i <= 7; i++)
            D[idx][i - 1] = D[idx][i];
        D[idx][7] = temp;
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int K; cin >> K;
        int sol = 0;
        for(int j = 1; j <= 4; j++)
            for(int k = 0; k < 8; k++)
                cin >> D[j][k];
        for(int c = 0; c < K; c++) {
            R[1] = R[2] = R[3] = R[4] = 0;
            int idx, dir; cin >> idx >> dir;
            R[idx] = dir;
            for(int j = idx + 1; j <= 4; j++) {
                if(D[j - 1][2] != D[j][6]) R[j] = R[j - 1] * -1;
                else break;
            }
            for(int j = idx - 1; j >= 1; j--) {
                if(D[j + 1][6] != D[j][2]) R[j] = R[j + 1] * -1;
                else break;
            }
            for(int j = 1; j <= 4; j++)
                if(R[j] != 0) rotate(j, R[j]);
        }
        int num = 1;
        for(int j = 1; j <= 4; j++) {
            if(D[j][0]) sol = sol + num;
            num = num * 2;
        }
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}