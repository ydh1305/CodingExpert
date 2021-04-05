#include <iostream>
using namespace std;

#define HASH_SIZE 1000
#define PN 23

char temp[1000][1000];
int R, C;

struct HashMap {
    char name[HASH_SIZE][1000];
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
        register int i = 0;
        for(; str[i]; i++)
            name[name_idx][i] = str[i];
        name[name_idx][i] = 0;
        
        unsigned int key = get_key(str);
        int& h_size = hash_table[key][0];
        hash_table[key][++h_size] = name_idx;

        name_idx++;
        return name_idx - 1;
    }
};
HashMap hm;

int binary_search(int s, int e) {
    int m;
    bool chk;
    while(s <= e) {
        chk = false;
        m = (s + e) / 2;
        hm.clear();
        for(int w = 0; w < C; w++) {
            int tmp_idx = 0;
            char tmp[1000] = { 0, };
            for(int h = m; h < R; h++) {
                tmp[tmp_idx++] = temp[h][w];
            }
            int ret = hm.contain(tmp);
            if(ret != -1) {
                chk = true;
                break;
            }
            hm.insert(tmp);
        }
        if(chk == true) e = m - 1;
        else s = m + 1;
    }
    if(chk == false) return m; 
    else return m - 1;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> R >> C;
    for(register int i = 0; i < R; i++) cin >> temp[i];
    cout << binary_search(0, R - 1) << '\n';

    return 0;
}
