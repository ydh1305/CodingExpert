#include <iostream>
#include <algorithm>
using namespace std;

int N, M;
int arr[100001];

long long binary_search(long long s, long long e) {
    long long sol = 0;
    while(s <= e) {
        long long m = (s + e) / 2;
        long long sum = 0;
        for(int i = 0; i < N; ++i) {
            sum = sum + (m / arr[i]);
            if(sum >= M) break;
        }
        if(sum >= M) {
            e = m - 1;
            sol = m;
        }
        else s = m + 1;
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N >> M;
        long long max = 0;
        for(register int i = 0; i < N; ++i) {
            cin >> arr[i];
            if(max < arr[i]) max = arr[i];
        }
        cout << '#' << t << ' ' << binary_search(1, max * M) << '\n';
    }
    return 0;
}