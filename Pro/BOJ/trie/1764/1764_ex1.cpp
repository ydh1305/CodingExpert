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
    T& operator [](int idx) {
        return arr[idx];
    }
    T operator [](int idx) const {
        return arr[idx];
    }
    T* begin() {
        return &arr[0];
    }
    T* end() {
        return &arr[0] + s;
    }
    bool empty() {
        return s == 0;
    }
    T& back() {
        return arr[s - 1];
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

int comp(string a, string b) {
    return a > b;
}

char tree[21];
int total;

struct Trie {
    int child;
    bool finish;
    Trie *Node[26];

    Trie() {
        child = 0;
        finish = false; 
        for(int i = 0; i < 26; i++) Node[i] = NULL;
    }
    void insert(char *str) {
        if(*str == '\0') {
            child++;
            finish = true;
            return;
        }
        int cur = *str - 'a';
        if(Node[cur] == NULL) Node[cur] = new Trie();
        Node[cur]->insert(str + 1);
    }
    bool find(char *str) {
        if(*str == '\0') return true;
        int cur = *str - 'a';
        if(Node[cur] == NULL) return false;
        return Node[cur]->find(str + 1);
    }
    void search(int idx) {
        if(finish == true) {
            tree[idx] = '\0';
            cout << tree << endl;
        }
        for(int i = 0; i < 26; i++) {
            if(Node[i]) {
                int cur = i + 'a';
                tree[idx] = cur;
                Node[i]->search(idx + 1);
            }
        }
    }
};

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    Trie *root = new Trie();
    _vector<string> v;
    int N, M;
    cin >> N >> M;
    for(int i = 0; i < N; i++) {
        cin >> tree;
        root->insert(tree);
    }
    for(int i = 0; i < M; i++) {
        cin >> tree;
        if(root->find(tree)) {
            v.push_back(tree);
            total++;
        }
    }
    _sort(v.begin(), v.end(), comp);
    cout << total << endl;
    while(!v.empty()) {
        cout << v.back() << endl;
        v.pop_back();
    }

    return 0;
}
