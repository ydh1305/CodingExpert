#include <iostream>
using namespace std;

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
            if(_size == capacity) {
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
        T& front() {
            return arr[0];
        }
        T& back() {
            return arr[_size - 1];
        }
        T& operator [](int idx){
            return arr[idx];
        }
        T operator [](int idx)const {
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

int main(void){
    _vector<_pair<int, string>> v;
    _vector<int> d;
    cout << v.empty() << "\n";
    v.push_back(_pair<int, string>(90, "YDH"));
    v.push_back(_pair<int, string>(80, "AAA"));
    v.push_back(_pair<int, string>(70, "BBB"));
    d.push_back(70);
    d.push_back(60);
    d.push_back(50);
    d.push_back(40);
    for(int i = 0; i < v.size(); i++)
        cout << v[i].second << ' ' << v.empty() << ' ';
    int a = d.front();
    int b = d.back();
    cout << a << ' ' << b << "\n";

    return 0;
}
