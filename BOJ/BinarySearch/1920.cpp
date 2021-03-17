#include <iostream>
#include <algorithm>

using namespace std;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N, M, T;
    int arr[100001];
    cin >> N;
    for(int i = 0; i < N; i++)
        cin >> arr[i];
    sort(arr, arr + N);
    cin >> M;
    for(int i = 0; i < M; i++){
        cin >> T;
        cout << binary_search(arr, arr + N, T) << '\n';
    }
    return 0;
}
