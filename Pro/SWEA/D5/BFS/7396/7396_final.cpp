#include <iostream>
using namespace std;

#define NULL 0

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
    T& operator [](int idx) {
        return arr[idx];
    }
    T operator [](int idx) const {
        return arr[idx];
    }
};

template <typename T>
class _queue {
public:
    struct Node {
        T v;
        Node *next;
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
        if(head == NULL)
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
        delete temp;
        s--;
    }
    bool empty() const {
        return s == 0;
    }
    T front() const {
        return head->v;
    }
    T back() const {
        return tail->v;
    }
    int size() const {
        return s;
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
string sol;
int H, W;

int hh[2] = { 1, 0 };
int ww[2] = { 0, 1 };

void BFS(int y, int x) {
    _queue<_pair<int, int>> q;
    q.push({y, x});
    visit[y][x] = true;
    sol = "";
    sol = sol + map[y][x];

    while(!q.empty()) {
        char min = 'z';
        int q_size = q.size();
        _vector<_pair<int, int>> v;
        for(int i = 0; i < q_size; i++) {
            int data_h = q.front().first; 
            int data_w = q.front().second; 
            q.pop();
            if(data_h == H - 1 && data_w == W - 1) return;
            for(int j = 0; j < 2; j++) {
                int h = data_h + hh[j]; 
                int w = data_w + ww[j]; 
                if(h < 0 || h > H - 1 || w < 0 || w > W - 1) continue;
                if(visit[h][w] == true) continue;
                if(map[h][w] <= min) {
                    if(map[h][w] < min) v.clear();
                    v.push_back({h, w});
                    visit[h][w] = true;
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
        for(int j = 0; j < H; j++) cin >> map[j];
        for(int j = 0; j < H; j++)
            for(int k = 0; k < W; k++) visit[j][k] = false;
        BFS(0, 0);
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}
