#include <iostream>
using namespace std;

int N, X, Y;
int arr[1000];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N >> X >> Y;
        for(int i = 0; i < N; ++i)
            cin >> arr[i];
    }
    return 0;
}