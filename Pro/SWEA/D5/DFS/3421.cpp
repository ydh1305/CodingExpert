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
        void clear() {
            delete[] arr;
            s = 0;
            c = 32;
            arr = new T[c];
        }
        T& operator [](int idx) {
            return arr[idx];
        }
        T operator [](int idx) const {
            return arr[idx];
        }
};
_vector<int> v;

int N, M;
int total;
bool visit[21];
bool dp[21][21];

bool check(int s) {
    for(int i = 0; i < v.size(); i++) {
        int e = v[i];
        if(dp[s][e] == true) return true;
    }
    return false;
}

int DFS(int idx) {
    total++;
    for(int i = idx; i <= N; i++) {
        if(visit[i] == true) continue;
        if(check(i) == true) continue;
        visit[i] = true;
        v.push_back(i);
        DFS(i + 1);
        v.pop_back();
        visit[i] = false;
    }
    return total;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N >> M;
        int x, y;
        v.clear();
        total = 0;
        for(int j = 0; j < 21; j++)
            for(int k = 0; k < 21; k++) dp[j][k] = 0;
        for(int j = 0; j < 21; j++) visit[j] = 0;
        for(int j = 0; j < M; j++) {
            cin >> x >> y;
            dp[x][y] = true;
            dp[y][x] = true;
        }
        cout << '#' << i << ' ' << DFS(1) << '\n';
    }
    return 0;
}
