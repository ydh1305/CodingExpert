#include <bits/stdc++.h>
using namespace std;

#define MAX 5000
int arr[MAX];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int N; cin >> N;
        int last = -1;
        for(int j = 0; j < N; j++) {
            cin >> arr[j];
            last = max(last, arr[j]);
        }     
        sort(arr, arr + N);
        int s = 0, e = 0;
        for(int j = 1; j < N; j++) {
            if(arr[j] == arr[j - 1] + 1) {
                if(arr[j] < last) {
                    e = j + 1;
                    while(e < N && arr[e] == arr[j]) e++;
                    swap(arr[j], arr[e]);
                }
                else {
                    s = j - 1;
                    while(s >= 0 && arr[s] == arr[j - 1]) s--;
                    swap(arr[j], arr[s + 1]);
                }
            }
        }
        cout << '#' << i << ' ';
        for(register int j = 0; j < N; j++)
             cout << arr[j] << ' ';
        cout << '\n';
    }
    return 0;
}