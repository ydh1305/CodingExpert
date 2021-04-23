#include <bits/stdc++.h>
using namespace std;

#define MAX 10000
int arr[MAX + 1];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int N, M; cin >> N >> M;
        for(int j = 0; j < N; j++)
            cin >> arr[j];
        int s = 0, e = 0;
        int sol = 0, sum = 0;
        while(s < N && e < N) {
            while(sum < M && e < N) {
                sum = sum + arr[e];
                e++;
            }
            if(sum == M) sol++;
            sum = sum - arr[s];
            s++;
        }
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}