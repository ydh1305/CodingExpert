using namespace std;

#define MAX 30000
#define min(a,b) ((a>b)?(b):(a))
#define max(a,b) ((a>b)?(a):(b))

int base[MAX], diff[MAX], sum[MAX], ss[MAX];
bool visit[MAX];

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

template <typename T>
class _vector {
    public:
        int _size;
        int capacity;
        T *arr;
        _vector() {
            _size = 0;
            capacity = 32;
            arr = new T[capacity];
        }
        _vector(int k) {
            _size = k;
            capacity = k;
            arr = new T[capacity];
        }
        ~_vector() {
            delete[] arr;
        }
        void clear() {
            delete[] arr;
            _size = 0;
            capacity = 32;
            arr = new T[capacity];
        }
        int size() {
            return _size;
        }
        int resize(int k) {
           T *temp;
           temp = new T[k];
           for(int i = 0; i < _size; i++)
               temp[i] = arr[i];
           delete[] arr;
           arr = temp; 
           _size = capacity = k;
        }
        T* begin() const {
            return &arr[0];
        }
        T* end() const {
            return &arr[0] + _size;
        }
        void push_back(T val) {
            if(_size == capacity) {
                resize(_size * 2);
                _size /= 2;
            }
            arr[_size++] = val;
        }
        void pop_back() {
            _size--;
        }
        bool empty() {
            return _size == 0;
        }
        T& back() {
            return arr[_size - 1];
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

int comp(const _pair<int, int> &a, const _pair<int, int> &b){
    if(a.first == b.first) 
        return a.second < b.second;
    return a.first < b.first;
}

int comp1(const int a, const int b){
    return a < b;
}

int lower_bound(int s, int e, int f) {
    while(s < e) {
        int m = (s + e) / 2;
        if(ss[m] < f) s = m + 1;
        else e = m;
    }
    return e;
}

int get_idx(int f) {
    int it = lower_bound(0, MAX - 1, f);
    if(ss[it] != f) return -1;
    return it;
}

void flip(int map[4][4]){
    for(int i = 0; i < 4; i++){
        _swap(map[i][0], map[i][3]);
        _swap(map[i][1], map[i][2]);
    }
}

void rotate(int map[4][4]){
    int temp[4][4];
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            temp[j][3 - i] = map[i][j]; 
        }
    }
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            map[i][j] = temp[i][j]; 
        }
    }
}

_pair<int, int> block[MAX];
_vector<int> v[MAX];

int makeBlock(int module[][4][4]) {
    for(int i = 0; i < MAX; i++) v[i].clear();
    for(int i = 0; i < MAX; i++) {
        visit[i] = false;
        base[i] = 10;
        for(int j = 0; j < 4; j++) {
            for(int k = 0; k < 4; k++) {
                base[i] = min(base[i], module[i][j][k]); 
            }
        }
        diff[i] = 0;
        sum[i] = 0;
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

    for(int i = 0; i < MAX; i++){
        int idx = block[i].second;
        v[get_idx(sum[idx])].push_back(idx);
    }

    int ret = 0;
    for(int i = MAX - 1; i >= 0; i--){
        int idx = block[i].second;
        if(visit[idx]) continue;
        visit[idx] = true;
        v[get_idx(sum[idx])].pop_back();
        int temp[4][4];
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                temp[j][k] = module[idx][j][k];               
            }
        }
        flip(temp);
        for(int j = 0; j < 4; j++){
            if(j) rotate(temp);
            int tsum = 0;
            for(int h = 0; h < 4; h++){
                for(int w = 0; w < 4; w++){
                    tsum = tsum * 3 + (diff[idx] - (temp[h][w] - base[idx]));
                }
            }
            tsum = get_idx(tsum);
            if(tsum == -1 || v[tsum].empty()) continue;
            int it = v[tsum].back();
            visit[it] = true;
            ret += base[idx] + base[it] + diff[it];
            v[tsum].pop_back();
            break;
        }
    }
    return ret;
}
