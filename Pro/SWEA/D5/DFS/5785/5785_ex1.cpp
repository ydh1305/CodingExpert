#include <bits/stdc++.h>
using namespace std;

#define MAX 20
long long arr[MAX][MAX];
bool visit[1 << 21];
bool check[MAX];
int sol[MAX];
int sol_cnt;
int N;

void DFS(int bits, int cnt) {
    if(visit[bits]) return;
    visit[bits] = true;
    if(cnt == N - 1) {
        for(int i = 0; i < N; i++) {
            if((bits & (1 << i)) == 0) {
                if(!check[i]) {
                    check[i] = true;
                    sol[sol_cnt++] = i + 1;
                    break;
                }
            }
        }
    }
    for(int i = 0; i < N; i++) {
        if((bits & (1 << i)) == 0) {
            long long sum = 0;
            for(int j = 0; j < N; j++) {
                if((bits & (1 << j)) == 0)
                    sum = sum + arr[i][j];
            }
            if(sum > 0)
                DFS((bits | (1 << i)), cnt + 1);
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N;
        sol_cnt = 0;
        memset(check, false, sizeof(check));
        memset(visit, false, sizeof(visit));
        memset(sol, 0, sizeof(sol));
        for(int h = 0; h < N; h++)
            for(int w = 0; w < N; w++)
                cin >> arr[h][w];
        DFS(0, 0);
        sort(sol, sol + sol_cnt);
        cout << '#' << i << ' ' << sol_cnt << ' ';
        for(int j = 0; j < sol_cnt; j++)
            cout << sol[j] << ' ';
        cout << '\n';
    }
    return 0;
}