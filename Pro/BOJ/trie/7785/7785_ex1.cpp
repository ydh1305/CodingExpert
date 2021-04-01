#include <iostream>
using namespace std;

#define HASH_SIZE 1000000
#define PN 23

struct HashMap {
    char name[HASH_SIZE][6];
    int hash_table[HASH_SIZE][10];
    int name_idx;

    void clear(void) {
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
            if(_strcmp(str, name[i]) == 0)
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
    void remove(char *str) {
        unsigned int key = get_key(str);
        int h_size = hash_table[key][0];
        for(int i = 1; i <= h_size; i++) {
            int pos = hash_table[key][i];
            if(_strcmp(str, name[pos]) == 0) {
                int j = 0;
                for(; str[j]; j++)
                    name[pos][j] = 0;
                name[pos][j] = '\0';
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

int comp(char *a, char *b) {
    int i = 0;
    while(a[i]) {
        if(a[i] != b[0]) break;
        i++;
    }
    return a[i] - b[i];
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int N; cin >> N;
    char s1[6], s2[6];
    for(register int i = 0; i < N; i++) {
        cin >> s1 >> s2;
        if(s2[0] == 'e') hm.insert(s1); 
        if(s2[0] == 'l') hm.remove(s1); 
    }
    _sort(hm.name, hm.name + hm.name_idx, comp);
    for(register int i = 0; i < hm.name_idx; i++) {
        //if(hm.name[i] == NULL) break;
        cout << hm.name[i] << '\n';
    }

    return 0;
}
