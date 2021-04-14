#include <iostream>
using namespace std;

#define HASH_SIZE 20000
#define PN 23

int cnt[HASH_SIZE];
int bucket[HASH_SIZE];
int bucket_idx;
struct HashMap {
    int num[HASH_SIZE];
    int hash_table[HASH_SIZE][10];
    int num_idx;

    void clear() {
        num_idx = 0;
        for(int i = 0; i < HASH_SIZE; i++)
            hash_table[i][0] = 0;
    }
    unsigned int get_key(int data) {
        unsigned int key = 0, p = PN;
        key = (long long)data * p;
        return key % HASH_SIZE;
    }
    int contain(int data) {
        unsigned int key = get_key(data);
        int h_size = hash_table[key][0];
        for(int i = 1; i <= h_size; i++) {
            int pos = hash_table[key][i];
            if(data == num[pos])
                return pos;
        }
        return -1;
    }
    int insert(int data) {
        num[num_idx] = data;
        unsigned int key = get_key(data);
        int& h_size = hash_table[key][0];
        hash_table[key][++h_size] = num_idx;
        num_idx++;
        return num_idx - 1;
    }
};
HashMap hm;

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
        T* begin() {
            return &arr[0];
        }
        T* end() {
            return &arr[0] + s;
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
    return a.second < b.second; 
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    _vector<_pair<int, int>> v;
    int T; cin >> T;
    for(int i = 0; i < T; i++) {
        int N; cin >> N;
        hm.clear();
        v.clear();
        bucket_idx = 0;
        for(int j = 0; j < HASH_SIZE; j++) cnt[j] = 0;
        for(int j = 0; j < N; j++) bucket[j] = 0;
        for(int j = 0; j < N; j++) {
            int num;
            for(int k = 0; k < 5; k++) {
                cin >> num;
                int idx = hm.contain(num);
                if(idx == -1) idx = hm.insert(num);
                cnt[idx] += (k + 1); 
                if(j == 0) bucket[bucket_idx++] = idx;
            }
        }
        for(int j = 0; j < bucket_idx; j++) {
            v.push_back({ bucket[j], cnt[bucket[j]] });
        }
        _sort(v.begin(), v.end(), comp); 
        cout << '#' << i + 1 << ' ';
        for(int j = 0; j < bucket_idx; j++)
            cout << hm.num[v[j].first] << ' ';
        cout << '\n';
    }

    return 0;
}
