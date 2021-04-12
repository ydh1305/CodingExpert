#include <iostream>
using namespace std;

#define HASH_SIZE 200000
#define PN 23

struct HashMap {
    char name[HASH_SIZE][21];
    int hash_table[HASH_SIZE][10];
    int name_idx;

    void clear() {
        name_idx = 0;
        for(int i = 0; i < HASH_SIZE; i++)
            hash_table[i][0] = 0;
    }
    unsigned int get_key(char *str) {
        unsigned int key = 0, p = 1;
        for(int i = 0; str[i]; i++) {
            key = key + (str[i] * p);
            p = p * PN;
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
        name[name_idx][i] = '\0';

        unsigned int key = get_key(str);
        int& h_size = hash_table[key][0];
        hash_table[key][++h_size] = name_idx;
        
        name_idx++;
        return name_idx - 1;
    }
};
HashMap hm;

#define max(a,b) ((a>b)?(a):(b))
int p[HASH_SIZE];

int find(int n) {
    if(p[n] < 0) return n;
    return p[n] = find(p[n]);
}

int merge(int a, int b) {
    a = find(a);
    b = find(b);

    if(a == b) return -p[a];
    if(p[a] < p[b]) {
        p[a] += p[b];
        p[b] = a;
    }
    else {
        p[b] += p[a];
        p[a] = b;
    }
    return max(-p[a], -p[b]);
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 0; i < T; i++) {
        int N; cin >> N;
        hm.clear();
        for(int j = 0; j < 2 * N; j++) p[j] = -1;
        for(int j = 0; j < N; j++) {
            char s1[21], s2[21];
            cin >> s1 >> s2;
            int it1 = hm.contain(s1);
            int it2 = hm.contain(s2);
            if(it1 == -1) it1 = hm.insert(s1);
            if(it2 == -1) it2 = hm.insert(s2);
            cout << merge(it1, it2) << '\n';
        }    
    }

    return 0;
}