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

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    _vector<int> v;
    _vector<char> sol;
    for(int i = 0; i < T; i++) {
        int N; cin >> N;
        v.clear(); 
        sol.clear();
        int temp[100001];
        int idx = 0;
        for(int j = 0; j < 100000; j++) temp[j] = 0;
        for(int j = 0; j < N; j++) cin >> temp[j];
        for(int j = 1; j <= N; j++) {
            v.push_back(j); sol.push_back('+');
            while(v.back() == temp[idx] && idx < N) {
                v.pop_back(); sol.push_back('-');
                idx++;
            }
        }
        cout << '#' << i + 1 << ' ';
        if(N == idx) {
            for(int k = 0; k < sol.size(); k++)
                cout << sol[k];
            cout << '\n';
        }
        else
            cout << "NO" << '\n';
    }
    
    return 0;
}
