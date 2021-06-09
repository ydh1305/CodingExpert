#include <iostream>
using namespace std;

int N, tn;
int R[1000], L[1000];
int CPU[5];
unsigned char dp[1000][11][11][11][11][11];

bool DFS(int n, int nCPU) {
    if(n == N) return true;
    char q[5] = { 0, };
    for(int i = 0; i < nCPU; i++) {
        if(CPU[i] < R[n])
            q[i] = 0;
        else
            q[i] = CPU[i] - R[n];
    }
    unsigned char& visit = dp[n][q[0]][q[1]][q[2]][q[3]][q[4]];
    if(visit == tn * 5 + nCPU) return false;
    visit = tn * 5 + nCPU;
    for(int i = 0; i < nCPU; i++) {
        if(CPU[i] - R[n] + L[n] > 10) continue;
        int temp = CPU[i];
        if(!q[i])
            CPU[i] = R[n] + L[n];
        else
            CPU[i] = CPU[i] + L[n];
        if(DFS(n + 1, nCPU)) {
            CPU[i] = temp;
            return true;
        }
        CPU[i] = temp;
    }
    return false;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(tn = 1; tn <= T; tn++) {
        cin >> N;
        for(int j = 0; j < N; j++)
            cin >> R[j] >> L[j];
        int sol = -1;
        for(int j = 1; j <= 5; j++) {
            if(DFS(0, j)) {
                sol = j;
                break;
            }
        }
        cout << '#' << tn << ' ' << sol << '\n';
    }
    return 0;
}