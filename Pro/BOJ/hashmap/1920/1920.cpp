#include <iostream>
using namespace std;

int arr[100001];

template <typename It>
void _swap(It &a, It &b) {
    It c(a); a = b; b = c;
}

template <typename It, typename Cmp>
void _sort(It begin, It end, Cmp cmp) {
    if(begin == end) return;
    _swap(*begin, *((end - begin) / 2 + begin));
    It pi = begin;
    It le = begin + 1;
    It ri = end - 1;
    while(le <= ri) {
        while(le <= ri && !cmp(*pi, *le)) le++;
        while(le <= ri && !cmp(*ri, *pi)) ri--;
        if(le <= ri) _swap(*le, *ri);
    }
    _swap(*pi, *ri);
    _sort(begin, ri, cmp);
    _sort(ri + 1, end, cmp);
}

int comp(const int a, const int b) {
    return a < b;
}

int lower_bound(int s, int e, int f) {
    while(s <= e) {
        int m = (s + e) / 2;
        if(arr[m] == f) return 1;
        else if(arr[m] < f) s = m + 1;
        else if(arr[m] > f) e = m - 1;
    }
    return 0;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int N; cin >> N;
    for(register int i = 0; i < N; i++) cin >> arr[i];
    _sort(arr, arr + N, comp);
    int M, X; cin >> M;
    for(register int i = 0; i < M; i++) {
       cin >> X;
       cout << lower_bound(0, N - 1, X) << '\n';
    }

    return 0;
}
