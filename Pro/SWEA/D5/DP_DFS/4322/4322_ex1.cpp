#include <iostream>
using namespace std;

int tn, N;
int R[1001], L[1001];
int CPU[5];
unsigned char dp[10001][11][11][11][11][11];

bool DFS(int n, int cpuN) {
    if(n == N) return true;
    char q[5] = { 0, };
    for(int i = 0; i < cpuN; i++) {
        if(R[n] > CPU[i])
            q[i] = 0;
        else
            q[i] = CPU[i] - R[n];
    }
    unsigned char& visit = dp[n][q[0]][q[1]][q[2]][q[3]][q[4]];
    if(visit == tn * 5+ cpuN) return false;
    visit = tn * 5 + cpuN;
    for(int i = 0; i < cpuN; i++) {
        if(CPU[i] - R[n] + L[n] > 10) continue;
        int temp = CPU[i];
        if(!q[i])
            CPU[i] = R[n] + L[n];
        else
            CPU[i] = CPU[i] + L[n];
        if(DFS(n + 1, cpuN)) {
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
        for(int i = 0; i < N; i++)
            cin >> R[i] >> L[i];
        int sol = -1;
        for(int i = 1; i <= 5; i++) {
            if(DFS(0, i)) {
                sol = i;
                break;
            }
        }
        cout << '#' << tn << ' ' << sol << '\n';
    }
    return 0;
}