#include <iostream>
#include <algorithm>
using namespace std;

int arr[5001];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int N; cin >> N;
        int last = 0;
        for(int i = 0; i < N; ++i) {
            cin >> arr[i];
            if(last < arr[i]) last = arr[i];
        }
        sort(arr, arr + N);
        for(int i = 1; i < N; ++i) {
            if(arr[i] == arr[i - 1] + 1) {
                if(arr[i] < last) {
                    int idx = i + 1;
                    while(idx < N && arr[i] == arr[idx]) idx++;
                    swap(arr[i], arr[idx]);
                } else {
                    int idx = i - 1;
                    while(idx >= 0 && arr[i - 1] == arr[idx]) idx--;
                    swap(arr[i], arr[idx + 1]);
                }
            }
        }
        cout << '#' << t << ' ';
        for(int i = 0; i < N; i++)
            cout << arr[i] << ' ';
        cout << '\n';
    }
    return 0;
}