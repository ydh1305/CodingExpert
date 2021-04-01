#include <iostream>
using namespace std;

#define NULL 0

char temp[6];

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
            for(int i = 0; i < s; i++) temp[i] = arr[i];
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

struct Trie {
    int child;
    bool finish;
    Trie *Node[63];

    Trie() {
        child = 0;
        finish = false;
        for(int i = 0; i < 63; i++) Node[i] = NULL;
    }
    void insert(char *str) {
        child++;
        if(*str == '\0') {
            finish = true;
            return;
        }
        int cur = *str - 'A';
        if(Node[cur] == NULL) Node[cur] = new Trie();
        Node[cur]->insert(str + 1);
    }
    void search(int idx) {
        if(finish == true) {
            temp[idx] = '\0';
            v.push_back(temp);
        }
        for(int i = 62; i >= 0; i--) {
            if(Node[i]) {
                int cur = i + 'A';
                temp[idx] = cur;
                Node[i]->search(idx + 1);
            }
        }
    }
    void remove(char *str) {
        child--;
        if(*str == '\0') {
            finish = false;
        }
        else {
            int cur = *str - 'A';
            Node[cur]->remove(str + 1);
            if(!child) {
                delete Node[cur];
                Node[cur] = NULL;
            }
        }
    }
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

int comp(string a, string b){
    return a > b;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    Trie *root = new Trie();
    int N; cin >> N;
    char s1[6], s2[6];
    for(register int i = 0; i < N; i++) {
        cin >> s1 >> s2;
        if(s2[0] == 'e') root->insert(s1); 
        if(s2[0] == 'l') root->remove(s1); 
    }
    root->search(0);
    _sort(v.begin(), v.end(), comp);
    for(register int i = 0; i < v.size(); i++)
        cout << v[i] << '\n';

    return 0;
}
