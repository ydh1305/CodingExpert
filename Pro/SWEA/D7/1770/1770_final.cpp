using namespace std;

#define MAX 30000
#define min(a,b) ((a>b)?(b):(a))
#define max(a,b) ((a>b)?(a):(b))

int base[MAX], diff[MAX], sum[MAX], ss[MAX];
bool visit[MAX];

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

template <typename A, typename B>
struct _pair {
    A first;
    B second;
    _pair(A a, B b):first(a), second(b) {}
    _pair() {}
};

template <typename It>
void _swap(It &a, It &b) {
    It c(a); a = b; b = c;
}

template <typename It, typename Cmp>
void _sort(It begin, It end, Cmp cmp) {
    if(begin == end) return;
    _swap(*begin, *((end - begin) / 2 + begin));
    It pi = begin;
    It le = begin + 1;
    It ri = end - 1;
    while(le <= ri) {
        while(le <= ri && !cmp(*pi, *le)) le++;
        while(le <= ri && !cmp(*ri, *pi)) ri--;
        if(le <= ri) _swap(*le, *ri);
    }
    _swap(*pi, *ri);
    _sort(begin, ri, cmp);
    _sort(ri + 1, end, cmp);
}

int comp(_pair<int, int> &a, _pair<int, int> &b) {
    if(a.first == b.first)
        return a.second < b.second;
    return a.first < b.first;
}

int comp1(int a, int b) {
    return a < b;
}

int lower_bound(int s, int e, int d) {
    while(s < e) {
       int m = (s + e) / 2;
       if(ss[m] < d) s = m + 1;
       else e = m;
    }
    return e;
}

int get_idx(int d) {
    int it = lower_bound(0, MAX - 1, d);
    if(ss[it] != d) return -1;
    return it;
}

void flip(int map[4][4]) {
    for(int i = 0; i < 4; i++) {
        _swap(map[i][0], map[i][3]);
        _swap(map[i][1], map[i][2]);
    }
}

void rotate(int map[4][4]) {
    int temp[4][4];
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            temp[j][3 - i] = map[i][j];
        }
    }
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            map[i][j] = temp[i][j];
        }
    }
}

_pair<int, int> block[MAX];
_vector<int> v[MAX];

int makeBlock(int module[][4][4]) {
    for(int i = 0; i < MAX; i++) v[i].clear();
    for(register int i = 0; i < MAX; i++) {
        visit[i] = false;
        base[i] = 10;
        for(int j = 0; j < 4; j++) {
            for(int k = 0; k < 4; k++) {
                base[i] = min(base[i], module[i][j][k]);
            }
        }
        sum[i] = 0;
        diff[i] = 0;
        for(int j = 0; j < 4; j++) {
            for(int k = 0; k < 4; k++) {
                sum[i] = sum[i] * 3 + (module[i][j][k] - base[i]);
                diff[i] = max(diff[i], module[i][j][k] - base[i]);
            }
        }
        block[i] = { base[i] + diff[i], i };
        ss[i] = sum[i];
    }
    _sort(block, block + MAX, comp);
    _sort(ss, ss + MAX, comp1);
    for(register int i = 0; i < MAX; i++) {
        int idx = block[i].second;
        v[get_idx(sum[idx])].push_back(idx);
    }
    int ret = 0;
    for(register int i = MAX - 1; i >= 0; i--) {
        int idx = block[i].second;
        if(visit[idx]) continue;
        visit[idx] = true;
        v[get_idx(sum[idx])].pop_back();
        int temp[4][4];
        for(int j = 0; j < 4; j++)
            for(int k = 0; k < 4; k++)
                temp[j][k] = module[idx][j][k];
        flip(temp);
        for(int j = 0; j < 4; j++) {
            if(j) rotate(temp);
            int tsum = 0;
            for(int h = 0; h < 4; h++) {
                for(int w = 0; w < 4; w++) {
                    tsum = tsum * 3 + (diff[idx] - (temp[h][w] - base[idx]));
                }
            }
            tsum = get_idx(tsum);
            if(tsum == -1 || v[tsum].empty()) continue; 
            int it = v[tsum].back();
            v[tsum].pop_back();
            visit[it] = true;
            ret = ret + base[idx] + base[it] + diff[it];
            break;
        }
    }

    return ret;
}
