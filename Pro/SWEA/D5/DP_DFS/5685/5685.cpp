#include<iostream>
using namespace std;

int arr[101];
long long dp[101][21];
int N;

long long DFS(int n, int sum) {
    if(n == N - 2) {
        if(sum == arr[N - 1]) dp[n][sum] = 1;
        else dp[n][sum] = 0;
        return dp[n][sum];
    }
    if(dp[n][sum] >= 0) return dp[n][sum];
    dp[n][sum] = 0;

    if(sum + arr[n + 1] <= 20) dp[n][sum] = (dp[n][sum] + DFS(n + 1, sum + arr[n + 1])) % 1234567891; 
    if(sum - arr[n + 1] >= 0) dp[n][sum] = (dp[n][sum] + DFS(n + 1, sum - arr[n + 1])) % 1234567891; 
    return dp[n][sum];
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
    cin >> T;
	for(test_case = 1; test_case <= T; ++test_case) {
        cin >> N;
        for(int i = 0; i < N; i++)
            for(int j = 0; j <= 20; j++)
                dp[i][j] = -1;
        for(int i = 0; i < N; i++) arr[i] = 0;
        for(int i = 0; i < N; i++) cin >> arr[i];
        cout << '#' << test_case << ' ' << DFS(0, arr[0]) << '\n';
	}
	return 0;
}
