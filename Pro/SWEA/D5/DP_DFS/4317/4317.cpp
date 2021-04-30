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
        T *temp = new T[k];
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
    int size() {
        return s;
    }
    bool empty() {
        return s == 0;
    }
    T& front() {
        return &arr[0];
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

int H, W;
int arr[11][26];
bool visit[251];
bool check[11][26];
int len, sol, num;
_vector<_pair<int, int>> v;

void DFS(int idx, int cnt) {
    if(sol) {
        if(len - cnt < sol - cnt) return;
    }
    if(sol < cnt) sol = cnt;
    for(int i = idx; i < len; i++) {
        if(visit[i]) continue;
        int h = v[i].first; 
        int w = v[i].second;
        if(check[h][w] || check[h + 1][w] || check[h][w + 1] || check[h + 1][w + 1]) continue;
        check[h][w] = check[h + 1][w] = true;
        check[h][w + 1] = check[h + 1][w + 1] = true;
        visit[i] = true;
        DFS(i + 1, cnt + 1);
        visit[i] = false;
        check[h][w] = check[h + 1][w] = false;
        check[h][w + 1] = check[h + 1][w + 1] = false;
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> H >> W;
        for(int h = 0; h < H; h++)
            for(int w = 0; w < W; w++)
                check[h][w] = false;
        sol = 0; num = 0;
        v.clear();
        for(int h = 0; h < H; h++)
            for(int w = 0; w < W; w++)
                cin >> arr[h][w];
        for(int h = 0; h < H - 1; h++) {
            for(int w = 0; w < W - 1; w++) {
                if(!arr[h][w] && !arr[h + 1][w] && !arr[h][w + 1] && !arr[h + 1][w + 1])
                    v.push_back({h, w});
            }
        }
        len = v.size();
        DFS(0, 0);
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}