#include <iostream>
using namespace std;

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
        delete temp;
        s--;
    }
    T front() {
        return head->v;
    }
    T back() {
        return tail->v;
    }
    bool empty() {
        return s == 0;
    }
    int size() {
        return s;
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

#define MAX 51
#define INF (1 << 30)
char map[MAX][MAX];
bool visit[MAX][MAX];
int dtime[MAX][MAX];
int H, W;

int hh[4] = { -1, 1, 0, 0 };
int ww[4] = { 0, 0, -1, 1 };
_pair<int, _pair<int, int>> sp;
_pair<int, int> ep;
_vector<_pair<int, int>> devil;

int BFS(void) {
    _queue<_pair<int, _pair<int, int>>> q;
    q.push(sp);
    visit[sp.second.first][sp.second.second] = true;
    
    _queue<_pair<int, int>> qdev;
    for(int i = 0; i < devil.size(); i++) {
        dtime[devil[i].first][devil[i].second] = 0;
        qdev.push(devil[i]);
    }

    while(!qdev.empty()) {
        int dev_size = qdev.size();
        for(int i = 0; i < dev_size; i++) {
            int data_h = qdev.front().first;
            int data_w = qdev.front().second;
            qdev.pop();
            for(int j = 0; j < 4; j++) {
                int h = data_h + hh[j];
                int w = data_w + ww[j];
                if(h < 0 || w < 0 || h > H - 1 || w > W - 1) continue;
                if(map[h][w] == 'X' || map[h][w] == 'D') continue;
                if(dtime[h][w] > dtime[data_h][data_w] + 1) {
                    dtime[h][w] = dtime[data_h][data_w] + 1;
                    qdev.push({h, w});
                }
            }
        }
    }

    while(!q.empty()) {
        int q_size = q.size();
        for(int i = 0; i < q_size; i++) {
            int data_h = q.front().second.first;
            int data_w = q.front().second.second;
            int cnt = q.front().first;
            q.pop();
            for(int j = 0; j < 4; j++) {
                int h = data_h + hh[j];
                int w = data_w + ww[j];
                if(h < 0 || w < 0 || h > H - 1 || w > W - 1) continue;
                if(h == ep.first && w == ep.second) return cnt + 1;
                if(map[h][w] == 'X' || map[h][w] == '*') continue;
                if(visit[h][w] == true) continue;
                if(dtime[h][w] <= cnt + 1) continue;
                visit[h][w] = true;
                q.push({cnt + 1, {h, w}});
            }
        }
    }
    return -1;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> H >> W;
        for(int j = 0; j < MAX; j++)
            for(int k = 0; k < MAX; k++) visit[j][k] = false;
        for(int j = 0; j < MAX; j++)
            for(int k = 0; k < MAX; k++) dtime[j][k] = INF;
        sp = {0, {0, 0}};
        ep = {0, 0};
        devil.clear();
        for(int j = 0; j < H; j++) {
            for(int k = 0; k < W; k++) {
                char ch; cin >> ch;
                if(ch == 'D') ep = {j, k};
                else if(ch == 'S') sp = {0, {j, k}};
                else if(ch == '*') devil.push_back({j, k});
                map[j][k] = ch;
            }
        }
        int ret = BFS();
        if(ret == -1) 
            cout << '#' << i << ' ' << "GAME OVER" << '\n';
        else 
            cout << '#' << i << ' ' << ret << '\n';
    }

    return 0;
}
