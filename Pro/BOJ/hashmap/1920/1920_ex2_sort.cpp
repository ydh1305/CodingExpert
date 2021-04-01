#include <iostream>
using namespace std;

int num[100001];

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

int comp(int a, int b) {
    return a < b;
}

int binary_search(int s, int e, int data) {
    while(s <= e) {
        int m = (s + e) / 2;
        if(num[m] == data) return 1;
        else if(num[m] < data) s = m + 1;
        else if(num[m] > data) e = m - 1;
    }
    return 0;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int N; cin >> N;
    for(register int i = 0; i < N; i++) cin >> num[i];
    _sort(num, num + N, comp);
    int M; cin >> M;
    for(register int i = 0; i < M; i++) {
        int temp; cin >> temp;
        cout << binary_search(0, N - 1, temp) << '\n';
    }

    return 0;
}
