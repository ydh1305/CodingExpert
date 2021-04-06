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

#define MOD 1000000007
#define MAX 100001
#define W 0
#define B 1
long long dp[MAX][2];
_vector<int> v[MAX];

long long DFS(int cur, int c, int p) {
    if(dp[cur][c] != -1) return dp[cur][c];
    dp[cur][c] = 1;

    for(int i = 0; i < v[cur].size(); i++) {
        int next = v[cur][i]; 
        if(next == p) continue;
        if(c == W) {
            dp[cur][c] = dp[cur][c] * (DFS(next, W, cur) + DFS(next, B, cur)); 
            dp[cur][c] = dp[cur][c] % MOD;
        }
        else {
            dp[cur][c] = dp[cur][c] * DFS(next, W, cur); 
            dp[cur][c] = dp[cur][c] % MOD;
        }
    }
    return dp[cur][c];
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int N; cin >> N;
        for(int j = 1; j <= N; j++) v[j].clear();
        for(int j = 1; j <= N; j++) dp[j][0] = dp[j][1] = -1;
        for(int j = 0; j < N - 1; j++) {
            int x, y; cin >> x >> y;
            v[x].push_back(y); v[y].push_back(x);
        }
        cout << '#' << i << ' ' << (DFS(1, W, -1) + DFS(1, B, -1)) % MOD << '\n';
    }
    return 0;
}
