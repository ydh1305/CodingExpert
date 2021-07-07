#include <iostream>
#include <cstring>
using namespace std;

int N;
int arr[1000];
int dp[1000];

int DFS(int n) {
    if(n == N) return 0;
    int& sol = dp[n];
    if(sol != -1) return sol;
    sol = 0;
    for(int i = n; i < N; ++i) {
        int low = min(arr[n], arr[i]);
        int high = max(arr[n], arr[i]);
        sol = max(sol, DFS(i + 1) + high - low);
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    memset(dp, -1, sizeof(dp));
    for(int i = 0; i < N; ++i)
        cin >> arr[i];
    cout << DFS(0) << '\n';
    return 0;
}