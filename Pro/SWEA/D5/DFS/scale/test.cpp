#include <iostream>
#include <cstring>
using namespace std;

int A, B, N;
int arr[30];
bool dp[30][15000];
bool visit[30];

int abs(int n) {
    if(n < 0) return n * -1;
    return n;
}

void DFS(int n, int sum, int size) {
    if(n == size + 1) return;
    if(dp[n][sum] != false) return;
    dp[n][sum] = true;

    for(int i = 0; i < size; i++) {
        if(visit[i] == true) continue;
        visit[i] = true;
        DFS(n + 1, sum + arr[i], size);
        DFS(n + 1, sum, size);
        DFS(n + 1, abs(sum - arr[i]), size);
        visit[i] = false;
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> A >> B >> N;
        for(int j = 0; j < N; j++) cin >> arr[j];
        for(int j = 0; j < N; j++)
            for(int k = 0; k <= 15000; k++) dp[j][k] = false;
        DFS(0, 0, N);
        int flag = false;
        for(int j = A; j <= B; j++) {
            if(dp[N][j] == true) continue;
            flag = true;
        }
        cout << "#" << i << ' ';
        if(!flag) {
            cout << "0" << '\n';
        } else {  
            int max = 0;
            int sol;          
            for(int j = 1; j <= 300; j++) {
                if(dp[N][j] == true) continue;
                memset(dp, 0, sizeof(dp));
                arr[N] = j;
                DFS(0, 0, N + 1);
                int check = 0;
                for (int k = A; k <= B; k++) {
                    if (dp[N + 1][k] == true)
                        continue;
                    check++;
                }
                if(!check) {
                    sol = j;
                    break;
                } else {
                    if(max < check) {
                        max = check;
                        sol = j;
                    }
                } 
            }
            cout << sol << '\n';
        }
    }
    return 0;
}