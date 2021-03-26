#include <iostream>
#include <vector>
using namespace std;

template <typename It>
void _swap(It &a, It &b){
    It c(a); a = b; b = c;
}

template <typename It, typename Cmp>
void _sort(It begin, It end, Cmp cmp){
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

template <typename A, typename B>
struct _pair{
    A first;
    B second;
    _pair(A a, B b):first(a), second(b) {}
    _pair() {}
};

bool comp(const _pair<int, int> &a, const _pair<int, int> &b){
    if(a.first == b.first)
        return a.second < b.second;
    return a.first < b.first;
    // "<" 오름차순
    // ">" 내림차순
}

int main(void) {
    vector<_pair<int, int>> v;
    v.push_back(_pair<int, int>(70, 80));
    v.push_back(_pair<int, int>(70, 70));
    v.push_back(_pair<int, int>(70, 60));
    v.push_back(_pair<int, int>(70, 50));
    _sort(v.begin(), v.end(), comp);
    for(int i = 0; i < v.size(); i++)
        cout << v[i].first << v[i].second << "\n";

    return 0;
}
