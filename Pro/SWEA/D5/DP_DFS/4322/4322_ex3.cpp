#include <iostream>
using namespace std;

int N, t;
int rt[1000], pl[1000];
unsigned char dp[1000][11][11][11][11][11];
int CPU[5]; 

bool DFS(int n, int nCPU) {
    if(n == N) return true;
    unsigned char Q[5] = { 0, };
    for(int i = 0; i < nCPU; ++i) {
        if(CPU[i] < rt[n])
            Q[i] = 0;
        else
            Q[i] = CPU[i] - rt[n];
    }
    unsigned char& visit = dp[n][Q[0]][Q[1]][Q[2]][Q[3]][Q[4]];
    if(visit == t * 5 + nCPU) return false;
    visit = t * 5 + nCPU;
    for(int i = 0; i < nCPU; ++i) {
        if(CPU[i] - rt[n] + pl[n] > 10) continue;
        int temp = CPU[i];
        if(!Q[i])
            CPU[i] = rt[n] + pl[n];
        else
            CPU[i] = CPU[i] + pl[n];
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
    for(t = 1; t <= T; ++t) {
        cin >> N;
        for(int i = 0; i < N; ++i)
            cin >> rt[i] >> pl[i];
        int sol = -1;
        for(int i = 1; i <= 5; ++i) {
            if(DFS(0, i)) {
                sol = i;
                break;
            }
        }
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}