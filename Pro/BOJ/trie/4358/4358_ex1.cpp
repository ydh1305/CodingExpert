#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
class _vector {
    public:
        int s;
        int c;
        T *arr;
        _vector() {
            s = 0;
            c = 32;
            arr = new T[c];
        }
        _vector(int k) {
            s = k;
            c = k;
            arr = new T[c];
        }
        ~_vector() {
            delete[] arr;
        }
        void resize(int k) {
            T *temp;
            temp = new T[k];
            for(int i = 0; i < s; i++)
                temp[i] = arr[i];
            delete[] arr;
            arr = temp;
            s = c = k;
        }
        int size() {
            return s;
        }
        void push_back(T v) {
            if(s == c) {
                resize(s * 2);
                s /= 2;
            }
            arr[s++] = v;
        }
        void pop_back() {
            s--;
        }
        bool empty() {
            return s == 0;
        }
        T* begin() {
            return &arr[0];
        }
        T* end() {
            return &arr[0] + s;
        }
        T& back() {
            return arr[s - 1];
        }
        T& operator [](int idx) {
            return arr[idx];
        }
        T operator [](int idx) const {
            return arr[idx];
        }
};

template <typename A, typename B>
struct _pair {
    A first;
    B second;
    _pair(A a, B b):first(a), second(b) {}
    _pair() {}
};

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

int comp(string a, string b) {
    return a < b;
}

_vector<string> v1;
_vector<pair<string, float>> v2;

int main(void) {
    string s;
    while(true) {
        getline(cin, s);
        if(s.length() == 0) break;
        v1.push_back(s);
    }
    //_sort(v1.begin(), v1.end(), comp);
    sort(v1.begin(), v1.end());

    v2.push_back({v1[0], 1});
    for(int i = 1; i < v1.size(); i++) {
        if(v1[i] != v1[i - 1]) {
            v2.push_back({v1[i], 1});
        }
        else
            v2.back().second++;
    }
    for(int i = 0; i < v2.size(); i++) {
        v2[i].second = v2[i].second/v1.size() * 100;
        cout << v2[i].first << ' ';
        printf("%.4f\n", v2[i].second);
    }

    return 0;
}
