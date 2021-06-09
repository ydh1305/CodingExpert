#include <iostream>
using namespace std;

#define MAX 510
#define min(a,b) ((a>b)?(b):(a))
#define IMP (1 << 30)

int X[MAX], Y[MAX];
int dp[MAX][MAX];
int N, K;

int abs(int num) {
    if(num < 0) return (num * -1);
    return num;
}

int get_distance(int a, int b) {
    return abs(X[a] - X[b]) + abs(Y[a] - Y[b]); 
}

int DFS(int cur, int s) {
    if(cur == N - 1) return 0;
    if(dp[cur][s] != -1) return dp[cur][s]; 
    dp[cur][s] = IMP; 

    for(int i = 0; i <= K; i++) {
        int next = cur + i + 1; 
        if(next >= N) continue;
        if(s + i > K) continue; 
        dp[cur][s] = min(dp[cur][s], DFS(next, s + i) + get_distance(cur, next));
    }
    return dp[cur][s];
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 0; i < T; i++) {
        cin >> N >> K;
        for(int j = 0; j < MAX; j++)
            for(int k = 0; k < MAX; k++)
                dp[j][k] = -1;
        for(int j = 0; j < N; j++) {
            cin >> X[j] >> Y[j];
        }
        cout << '#' << i + 1 << ' ' << DFS(0, 0) << '\n'; 
    }
    return 0;
}