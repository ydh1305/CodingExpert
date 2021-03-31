#include <iostream>
using namespace std;

#define max(a,b) ((a>b)?(a):(b))

int parent[200002], fcount[200002];

template <typename K, typename T>
struct _map {
    struct node {
        node *l, *r, *p;
        K key;
        T val;
    };
    node *root;
    _map():root(0) {}
    ~_map() {
        while(root)
            erase(root->key);
    }
    void rotate(node *x) {
        node *p = x->p;
        node *b;
        if(x == p->l) {
            p->l = b = x->r;
            x->r = p;
        }
        else {
            p->r = b = x->l;
            x->l = p;
        }
        x->p = p->p;
        p->p = x;
        if(b) b->p = p;
        (x->p ? p == x->p->l ? x->p->l : x->p->r : root) = x;
    }
    void splay(node *x) {
        while(x->p) {
            node *p = x->p;
            node *g = p->p;
            if(g) rotate((x == p->l) == (p == g->l) ? p : x);
            rotate(x);
        }
    }
    void insert(K key, T val) {
        node *p = root, **pp;
        if(!p) {
            node *x = new node;
            root = x;
            x->l = x->r = x->p = 0;
            x->key = key;
            x->val = val;
            return;
        }
        while(true) {
            if(key == p->key) return;
            if(key < p->key) {
                if(!p->l) {
                    pp = &p->l;
                    break;
                }
                p = p->l;
            }
            else {
                if(!p->r) {
                    pp = &p->r;
                    break;
                }
                p = p->r;
            }
        }
        node *x = new node;
        *pp = x;
        x->l = x->r = 0;
        x->p = p;
        x->key = key;
        x->val = val;
        splay(x);
    }
    bool find(K key) {
        node *p = root;
        if(!p) return false;
        while(p) {
            if(key == p->key) break;
            if(key < p->key) {
                if(!p->l) break;
                p = p->l;
            }
            else {
                if(!p->r) break;
                p = p->r;
            }
        }
        splay(p);
        return key == p->key;
    }
    void erase(K key) {
        if(!find(key)) return;
        node *p = root;
        if(p->l) {
            if(p->r) {
                root = p->l;
                root->p = 0;
                node *x = root;
                while(x->r) x = x->r;
                x->r = p->r;
                p->r->p = x;
                delete p;
                return;
            }
            root = p->l;
            root->p = 0;
            delete p;
            return;
        }
        if(p->r) {
            root = p->r;
            root->p = 0;
            delete p;
            return;
        }
        root = 0;
    }
    void clear() {
        while(root)
            erase(root->key);
    }
    int count(K key) {
        return find(key);
    }
    T& operator [](K key) {
        if(!find(key)) insert(key, T(0));
        return root->val;
    }
};

template <typename It>
void _swap(It &a, It &b) {
    It c(a); a = b; b = c;
}

int findparent(int node) {
    if(node == parent[node]) return node;

    return parent[node] = findparent(parent[node]);
}

void merge(int a, int b) {
    a = findparent(a);
    b = findparent(b);

    if(a != b) {
        if(fcount[a] < fcount[b]) _swap(a, b);
        parent[b] = a;
        fcount[a] += fcount[b];
        fcount[b] = 0;
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int N, M;
    cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> M;
        for(int j = 0; j < 2 * M; j++) {
            parent[j] = j;
            fcount[j] = 1;
        }
        _map<string, int> name;
        int idx = 1;

        for(int j = 0; j < M; j++) {
            string s1, s2;
            cin >> s1 >> s2;

            if(name.count(s1) == 0) 
                name[s1] = idx++;
            if(name.count(s2) == 0)
                name[s2] = idx++;

            int v1 = findparent(name[s1]);
            int v2 = findparent(name[s2]);

            if(v1 == v2) cout << max(fcount[v1], fcount[v2]) << "\n"; 
            else {
                merge(v1, v2);
                cout << max(fcount[v1], fcount[v2]) << "\n";
            }
        }
    }
    return 0;
}
