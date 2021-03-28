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
        void resize(int k) {
            T *temp;
            temp = new T[k];
            for(int i = 0; i < _size; i++)
                temp[i] = arr[i];
            delete[] arr;
            arr = temp;
            capacity = _size = k;
        }
        int size() {
            return _size;
        }
        void push_back(int val) {
            if(_size == capacity) {
                resize(_size * 2);
                _size /= 2;
            }
            arr[_size++] = val;
        }
        bool empty() {
            return _size == 0;
        }
        void pop_back() {
            _size--;
        }
        T* begin() {
            return &arr[0];
        }
        T* end() {
            return &arr[0] + _size;
        }
        T& back() {
            return arr[_size - 1];
        }
        T& operator [](int idx) {
            return arr[idx];
        }
        T operator [](int idx) const {
            return arr[idx];
        }
};

template <typename It>
void _swap(It &a, It &b) {
    It c(a); a = b; b = c;
}

template <typename T>
struct _priority_queue {
        _vector<T> tree;
        int _size;
        _priority_queue() {
            tree.resize(1);
            _size = 0;
        }
        void push(T val) {
            tree.push_back(val);
            _size++;
            int idx = _size;
            while(idx > 1) {
                if(tree[idx] > tree[idx / 2])
                    _swap(tree[idx], tree[idx / 2]);
                else
                    break;
                idx /= 2;
            }
        }
        T top() {
            return tree[1];
        }
        bool empty() {
            return _size == 0;
        }
        void pop() {
            _swap(tree[1], tree[_size]);
            tree.pop_back();
            int idx = 1;
            _size--;
            while(true) {
                int next = -1;
                int cur = tree[idx];
                if(idx * 2 <= _size && cur < tree[idx * 2]) {
                    cur = tree[idx * 2];
                    next = idx * 2;
                }
                if(idx * 2 + 1 <= _size && cur < tree[idx * 2 + 1]) {
                    cur = tree[idx * 2 + 1];
                    next = idx * 2 + 1;
                }
                if(next == -1) break;
                _swap(tree[idx], tree[next]);
                idx = next;
            }
        }
};

int main(void) {
    _priority_queue<int> pq;
    pq.push(40);
    pq.push(90);
    pq.push(70);
    pq.push(60);
    pq.push(90);
    pq.push(100);
    while(!pq.empty()) {
        cout << pq.top() << "\n"; 
        pq.pop();
    }

    return 0;
}
