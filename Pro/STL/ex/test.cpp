#include <iostream>
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

int comp(const _pair<int, int> &a, const _pair<int, int> &b){
    if(a.first == b.first)
        return a.second < b.second;
    return a.first < b.first;
}

template <typename T>
class _vector {
    public:
        int _size;
        int capacity;
        T *arr;
        _vector() {
            _size = 0;
            capacity = 32;
            arr = new T[capacity];
        }
        _vector(int k) {
            _size = k;
            capacity = k;
            arr = new T[capacity];
        }
        ~_vector() {
            delete[] arr;
        }
        void clear() {
            delete[] arr;
            _size = 0;
            capacity = 32;
            arr = new T[capacity];
        }
        void resize(int k) {
            T *temp;
            temp = new T[k];
            for(int i = 0; i < _size; i++)
                temp[i] = arr[i];
            delete[] arr;
            arr = temp;
            _size = capacity = k;
        }
        int size() const {
            return _size;
        }
        T* begin() const {
            return &arr[0];
        }
        T* end() const {
            return &arr[0] + _size;
        }
        void push_back(T val) {
            if(_size == capacity){
                resize(_size * 2);
                _size /= 2;
            }
            arr[_size++] = val;
        }
        void pop_back() {
            _size--;
        }
        bool empty() {
            return _size == 0;
        }
        T& back() {
            return arr[_size - 1];
        }
        T& operator [](int idx){
            return arr[idx];
        }
        T operator [](int idx) const {
            return arr[idx];
        }
};

int comp1(int a, int b){
    return a < b;
}

int main(void){
#if 0
    _vector<_pair<int, int>> v;
    v.push_back(_pair<int, int>(70, 80));
    v.push_back(_pair<int, int>(70, 30));
    v.push_back(_pair<int, int>(70, 40));
    v.push_back(_pair<int, int>(70, 50));
#endif
    _vector<int> v;
    v.push_back(70);
    v.push_back(60);
    v.push_back(50);
    int block[10] = { 4, 3, 2, 6, 1, 5, 10, 9, 8, 7 };
#if 0
    _sort(v.begin(), v.end(), comp);
    for(int i = 0; i < v.size(); i++)
        cout << v[i].first << ' ' << v[i].second << "\n";
#else
    _sort(block, block + 10, comp1);
    int it = v.back();
    cout << it << "\n";
    for(int i = 0; i < 10; i++)
        cout << block[i] << "\n";
#endif
    
    return 0;
}
