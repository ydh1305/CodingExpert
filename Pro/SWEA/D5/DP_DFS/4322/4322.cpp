#include <iostream>
using namespace std;

int P[1001], L[1001];
unsigned char dp[1001][11][11][11][11][11];
int CPU[5];
int tn, N;

bool DFS(int n, int cnt) {
    if(n == N) return true;
    char wq[5] = { 0, };
    for(int i = 0; i < cnt; i++) {
        if(P[n] > CPU[i]) 
            wq[i] = 0;
        else
            wq[i] = CPU[i] - P[n];
    }
    unsigned char& check = dp[n][wq[0]][wq[1]][wq[2]][wq[3]][wq[4]];
    if(check == tn * 5 + cnt) return false;
    check = tn * 5 + cnt;

    for(int i = 0; i < cnt; i++) {
        if(CPU[i] - P[n] + L[n] > 10) continue;
        int temp = CPU[i];
        if(wq[i] == 0)
            CPU[i] = P[n] + L[n];
        else
            CPU[i] = CPU[i] + L[n];
        if(DFS(n + 1, cnt)) {
            CPU[i] = temp;
            return true;
        }
        CPU[i] = temp;
    }
    return false;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(tn = 1; tn <= T; tn++) {
        cin >> N;
        for(int j = 0; j < N; j++)
            cin >> P[j] >> L[j];
        int sol = -1;
        for(int j = 1; j <= 5; j++) {
            if(DFS(0, j)) {
                sol = j;
                break;
            }
        }
        cout << '#' << tn << ' ' << sol << '\n';
    }
}