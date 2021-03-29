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
        int size() {
            return s;
        }
        void resize(int k) {
            T *temp = new T[k];
            for(int i = 0; i < s; i++)
                temp[i] = arr[i];
            delete[] arr;
            arr = temp;
            s = c = k;
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
        void push(int v) {
            tree.push_back(v);
            s++;
            int idx = s;
            while(idx > 1) {
                if(tree[idx] < tree[idx / 2])
                    _swap(tree[idx], tree[idx / 2]);
                else break;
                idx /= 2;
            }
        }
        void pop() {
            _swap(tree[1], tree[s]);
            tree.pop_back();
            s--;
            int idx = 1;
            while(true) {
                int now = tree[idx];
                int next = -1;
                if(idx * 2 <= s && now > tree[idx * 2]) {
                    now = tree[idx * 2];
                    next = idx * 2;
                }
                if(idx * 2 + 1 <= s && now > tree[idx * 2 + 1]) {
                    now = tree[idx * 2 + 1];
                    next = idx * 2 + 1;
                }
                if(next == -1) break;
                _swap(tree[idx], tree[next]);
                idx = next;
            }
        }
        int top() {
            return tree[1];
        }
        bool empty() {
            return s == 0;
        }
        int size() {
            return s;
        }
};

int main(void) {
    int N, M;
    _priority_queue<int> pq;
    cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> M; 
        pq.push(M);
    }
    int sum = 0;
    while(pq.size() > 1) {
        int n1 = pq.top(); pq.pop();
        int n2 = pq.top(); pq.pop();
        sum = sum + (n1 + n2);
        pq.push(n1 + n2);
    }
    cout << sum << endl;

    return 0;
}
