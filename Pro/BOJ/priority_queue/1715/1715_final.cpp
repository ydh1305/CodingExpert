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
            T *temp;
            temp = new T[k];
            for(int i = 0; i < s; i++) temp[i] = arr[i];
            delete[] arr;
            arr = temp;
            s = c = k;
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
                int cur = tree[idx];
                int next = -1;
                if(idx * 2 <= s && cur > tree[idx * 2]) {
                    cur = tree[idx * 2];
                    next = idx * 2;
                }
                if(idx * 2 + 1 <= s && cur > tree[idx * 2 + 1]) {
                    cur = tree[idx * 2 + 1];
                    next = idx * 2 + 1;
                }
                if(next == -1) break;
                _swap(tree[idx], tree[next]);
                idx = next;
            }
        }
        bool empty() {
            return s == 0;
        }
        int top() {
            return tree[1];
        }
        int size() {
            return s;
        }
};

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    _priority_queue<int> pq;
    int N; cin >> N;
    int tmp, total = 0;
    for(register int i = 0; i < N; i++) {
        cin >> tmp; pq.push(tmp); 
    }
    while(pq.size() > 1) {
        int v1 = pq.top(); pq.pop();
        int v2 = pq.top(); pq.pop();
        total += (v1 + v2);
        pq.push(v1 + v2);
    }
    cout << total << '\n';

    return 0;
}
