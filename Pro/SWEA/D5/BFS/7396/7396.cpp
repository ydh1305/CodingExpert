#include <iostream>
using namespace std;

#define MAX 2001

char map[MAX][MAX];
bool visit[MAX][MAX];
char sol[MAX];
int H, W;

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

template <typename A, typename B>
struct _pair {
    A first;
    B second;
    _pair(A a, B b):first(a), second(b) {}
    _pair() {}
};

#if 0
struct Queue {
    int h;
    int w;
};
struct Queue queue[MAX * MAX * 10];
#endif

int wp, rp;
int cnt;
int hh[2] = { 1, 0 };
int ww[2] = { 0, 1 };

void BFS(int y, int x) {
    //struct Queue data;
    _vector<_pair<int, int>> Q;
    wp = rp = 0;
    cnt = 0;
    Q.push_back(y, x);
    //queue[wp].h = y; queue[wp++].w = x;
    visit[y][x] = true;
    sol[cnt++] = map[y][x];

    while(rp != wp) {
        char ch = 'z';
        _vector<_pair<int, int>> v;
        while(rp < wp) {
            _vector<_pair<int, int>> d;
            data = queue[rp++];
            if(data.h == H - 1 && data.w == W - 1) return;
            for(int i = 0; i < 2; i++) {
                int h = data.h + hh[i]; 
                int w = data.w + ww[i]; 
                if(h < 0 || h > H - 1 || w < 0 || w > W - 1) continue;
                if(visit[h][w] == true) continue;
                if(map[h][w] <= ch) {
                    if(map[h][w] < ch) v.clear();
                    v.push_back({h, w});
                    visit[h][w] = true;
                    ch = map[h][w];
                }
            }
        }
        for(int i = 0; i < v.size(); i++) 
            queue[wp].h = v[i].first, queue[wp++].w = v[i].second;
        sol[cnt++] = ch; 
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> H >> W;
        for(int j = 0; j < MAX; j++)
            for(int k = 0; k < MAX; k++) visit[j][k] = false;
        for(int j = 0; j < 2000; j++) sol[j] = 0;
        for(int h = 0; h < H; h++) cin >> map[h];
        BFS(0, 0);
        cout << '#' << i << ' ' << sol << '\n';
    }

    return 0;
}
