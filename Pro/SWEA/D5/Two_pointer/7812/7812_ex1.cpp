#include <iostream>
using namespace std;

int arr[10000];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int N, M; cin >> N >> M;
        for(int i = 0; i < N; ++i)
            cin >> arr[i];
        int s = 0, e = 0;
        int sum = 0, sol = 0;
        while(s < N) {
            while(e < N && sum + arr[e] <= M) {
                sum = sum + arr[e];
                if(sum == M) sol = sol + 1;
                e++;
            }
            sum = sum - arr[s];
            s++;
        }
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}