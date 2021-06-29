#include <iostream>
using namespace std;

int M;
int arr[21];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int N; cin >> N;
        for(int i = 1; i <= N; ++i)
            cin >> arr[i];
        cin >> M;
        int S[10001] = { 0, };
        S[0] = 1;
        for(int i = 1; i <= N; ++i) {
            for(int j = arr[i]; j <= M; ++j) {
                S[j] = S[j] + S[j - arr[i]];
            }
        }
        cout << S[M] << '\n';
    }
    return 0;
}