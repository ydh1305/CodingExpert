#include <iostream>
using namespace std;

int arr[1000001];
int N, M;
int max_v;

int binary_search(int s, int e, int v) {
    long long sum;
    int sol = 0;
    while(s <= e) {
        int m = (s + e) / 2;
        sum = 0;
        for(int i = 0; i < N; i++) {
            if(m < arr[i]) sum += (arr[i] - m); 
        }
        if(sum >= v) {
            sol = m;
            s = m + 1;
        }
        else e = m - 1;
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N >> M;
        max_v = 0;
        for(int j = 0; j < N; j++) {
            cin >> arr[j];
            if(max_v < arr[j]) max_v = arr[j];
        }
        cout << '#' << i << ' ' << binary_search(0, max_v, M) << '\n'; 
    }

    return 0;
}
