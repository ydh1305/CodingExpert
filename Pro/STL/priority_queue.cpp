#include <iostream>
using namespace std;

template <typename T>
class _vector {
    public: 
        int s;
        int c; 
        T * arr;
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
            c = s = k;
        }
        int size() {
            return s;
        }
        void push_back(int v) {
            if(c == s) {
                resize(s * 2);
                s /= 2;
            }
            arr[s++] = v;
        }
        void pop_back() {
            s--;
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

template <typename It>
void _swap(It &a, It &b) {
    It c(a); a = b; b = c;
}

template <typename T>
class _priority_queue {
    public:
        _vector<int> tree;
        int s;
        _priority_queue() {
            tree.resize(1);
            s = 0;
        }
        void push(T v) {
            tree.push_back(v);
            s++;
            int idx = s;
            while(idx > 1) {
                if(tree[idx] > tree[idx / 2])
                    _swap(tree[idx], tree[idx / 2]);
                else break;
                idx /= 2;
            }
        }
        T top() {
            return tree[1];
        }
        bool empty() {
            return s == 0;
        }
        void pop() {
            _swap(tree[1], tree[s]);
            tree.pop_back();
            s--;
            int idx = 1;
            while(true) {
                int next = -1;
                int cur = tree[idx];
                if(idx * 2 <= s && cur < tree[idx * 2]) {
                    cur = tree[idx * 2];
                    next = idx * 2;
                }
                if(idx * 2 + 1 <= s && cur < tree[idx * 2 + 1]) {
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
