#include <iostream>
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
        void clear() {
            delete[] arr;
            s = 0;
            c = 32;
            arr = new T[c];
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
        int size() const {
            return s;
        }
        T* begin() const {
            return &arr[0];
        }
        T* end() const {
            return &arr[0] + s;
        }
        void push_back(T val) {
            if(s == c) {
                resize(s * 2);
                s /= 2;
            }
            arr[s++] = val;
        }
        void pop_back() {
            s--;
        }
        bool empty() {
            return s == 0;
        }
        T& front() {
            return arr[0];
        }
        T& back() {
            return arr[s - 1];
        }
        T& operator [](int idx){
            return arr[idx];
        }
        T operator [](int idx) const {
            return arr[idx];
        }
        void operator =(const _vector<T> &v) {
            c = v.c;
            s = v.s;
            delete[] arr;
            arr = new T[c];
            for (int i = 0; i < s; i++)
                arr[i] = v[i];
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
