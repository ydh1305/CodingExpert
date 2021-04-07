#include <iostream>
using namespace std;

template <typename T>
class _queue {
public:
    struct Node {
        Node *next;
        T v;
        Node(T v):v(v), next(0) {}
        Node() {}
    };
    Node *head;
    Node *tail;
    int s;
    _queue() {
        head = tail = 0;
        s = 0;
    }
    void push(T v) {
        Node *temp = new Node(v);
        if(head == 0)
            head = tail = temp;
        else {
            tail->next = temp;
            tail = temp;
        }
        s++;
    }
    void pop() {
        Node *temp = head;
        head = head->next;
        delete[] temp;
        s--;
    }
    bool empty() {
        return s == 0;
    }
    int size() {
        return s;
    }
    T front() {
        return head->v;
    }    
    T back() {
        return tail->v;
    }
};

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
    void operator =(const _vector<T> &v) {
        delete[] arr;
        s = v.s;
        c = v.c;
        arr = new T[c];
        for(int i = 0; i < s; i++)
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

#define MAX 2001
char map[MAX][MAX];
bool visit[MAX][MAX];
int H, W;
string sol;

int hh[2] = { 1, 0 };
int ww[2] = { 0, 1 };

string BFS(int y, int x) {
    _queue<_pair<int, int>> q;
    q.push({y, x});
    visit[y][x] = true;
    sol = "";
    sol = sol + map[y][x];

    while(!q.empty()) {
        int q_size = q.size();
        _vector<_pair<int, int>> v;
        char min = 'z';
        for(int i = 0; i < q_size; i++) {
            int data_h = q.front().first;
            int data_w = q.front().second;
            q.pop();
            if(data_h == H - 1 && data_w == W - 1) return sol;
            for(int j = 0; j < 2; j++) {
                int h = data_h + hh[j];
                int w = data_w + ww[j];
                if(h < 0 || w < 0 || h > H - 1 || w > W - 1) continue;
                if(visit[h][w] == true) continue;
                if(min >= map[h][w]) {
                    if(min > map[h][w]) v.clear();
                    v.push_back({h, w});
                    min = map[h][w];
                }
            }
        }
        for(int i = 0; i < v.size(); i++) q.push(v[i]);
        sol = sol + min;
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> H >> W;
        for(int j = 0; j < H; j++)
            for(int k = 0; k < W; k++) visit[j][k] = false;
        for(int j = 0; j < H; j++) cin >> map[j];
        cout << '#' << i << ' ' << BFS(0, 0) << '\n';
    }

    return 0;
}