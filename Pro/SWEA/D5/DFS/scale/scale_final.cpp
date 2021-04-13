#include <bits/stdc++.h>
using namespace std;

int A, B, N;
int arr[31];
bool dp[31][15000];
bool visit[31];
bool check[501];

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
        memset(check, 0, sizeof(check));
        memset(visit, 0, sizeof(visit));
        memset(dp, 0, sizeof(dp));
        for(int j = 0; j < N; j++) {
            cin >> arr[j]; check[arr[j]] = true;
        }
        int sol = 0, min = (1 << 30), limit = 0, num = 1;
        bool flag = false;
        while(true) {
            DFS(0, 0, N);
            for(int j = A; j <= B; j++) {
                if(dp[N][j]) continue;
                limit++;
            }
            if(limit == (B - A + 1)) break;
            for(; num <= 500; num++) {
                if(check[num]) continue;
                break;
            }
            if(num == 501) break;
            if(!flag) {
                memset(dp, 0, sizeof(dp));
                N = N + 1;
                flag = true;
            }
            arr[N - 1] = num;
            if(min > limit) {
                min = limit;
                sol = num;
            }
        }
        cout << "#" << i << ' ' << sol << '\n';
    }
    return 0;
}