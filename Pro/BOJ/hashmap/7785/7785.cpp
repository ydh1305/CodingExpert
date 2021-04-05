#include <iostream>
using namespace std;

#define HASH_SIZE 1000000
#define PN 23

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
            s = c =k;
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
_vector<string> v;

struct HashMap {
    char name[HASH_SIZE][6];
    int hash_table[HASH_SIZE][10];
    int name_idx;

    void clear() {
        name_idx = 0;
        for(register int i = 0; i < HASH_SIZE; i++)
            hash_table[i][0] = 0;
    }
    unsigned int get_key(char *str) {
        unsigned int key = 0, p = 1;
        for(int i = 0; str[i]; i++) {
            key += str[i] * p;
            p *= PN;
        }
        return key % HASH_SIZE;
    }
    int _strcmp(char *a, char *b) {
        int i = 0;
        while(a[i]) {
            if(a[i] != b[i]) break;
            i++;
        }
        return a[i] - b[i];
    }
    int contain(char *str) {
        unsigned int key = get_key(str);
        int h_size = hash_table[key][0];
        for(int i = 1; i <= h_size; i++) {
            int pos = hash_table[key][i];
            if(_strcmp(str, name[pos]) == 0)
                return pos;
        }
        return -1;
    }
    int insert(char *str) {
        int i = 0;
        for(; str[i]; i++)
            name[name_idx][i] = str[i];
        name[name_idx][i] = 0;
        unsigned int key = get_key(str);
        int& h_size = hash_table[key][0];
        hash_table[key][++h_size] = name_idx;

        name_idx++;
        return name_idx - 1;
    }
    bool remove(char *str) {
        unsigned int key = get_key(str);
        int& h_size = hash_table[key][0];
        for(int i = 1; i <= h_size; i++) {
            int pos = hash_table[key][i];
            if(_strcmp(str, name[pos]) == 0) {
                for(int j = i + 1; j <= h_size; j++) {
                    hash_table[key][j - 1] = hash_table[key][j];
                }
                h_size--;
                return true;
            }
        }
        return false;
    }
    void search(void) {
        for(register int i = 0; i < HASH_SIZE; i++) {
            int h_size = hash_table[i][0];
            if(!h_size) continue;
            for(int j = 1; j <= h_size; j++) {
                int pos = hash_table[i][j];
                v.push_back(name[pos]);
            }
        }
    }
};
HashMap hm;

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

int comp(string a, string b) {
    return a > b;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    hm.clear();
    int N; cin >> N;
    char s1[6], s2[6];
    for(register int i = 0; i < N; i++) {
        cin >> s1 >> s2;
        if(s2[0] == 'e') hm.insert(s1); 
        if(s2[0] == 'l') hm.remove(s1);
    }
    hm.search();
    _sort(v.begin(), v.end(), comp);
    for(register int i = 0; i < v.size(); i++)
        cout << v[i] << '\n';

    return 0;
}
