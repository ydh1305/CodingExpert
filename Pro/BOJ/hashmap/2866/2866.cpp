#include <iostream>
using namespace std;

#define HASH_SIZE 1000
#define PN 23
    
int R, C;
string arr[1001];

struct HashMap {
    char name[HASH_SIZE][1001];
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
        register int i = 0;
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

int binary_search(int s, int e) {
    bool check;
    int m;
    while(s <= e) {
        hm.clear();
        m = (s + e) / 2;
        check = false;
        for(register int j = 0; j < C; j++){
            char temp[1001] = { 0, };
            int idx = 0;
            for(register int i = m; i < R; i++) temp[idx++] = arr[i][j]; 
            temp[idx] = '\0';

            int ret = hm.contain(temp);
            if(ret == -1) hm.insert(temp); 
            else check = true; 
        }
        if(check) e = m - 1;
        else s = m + 1;
    }
    if(check) return m - 1; 
    else return m;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> R >> C;
    for(int i = 0; i < R; i++) cin >> arr[i];
    cout << binary_search(0, R - 1) << '\n';

    return 0;
}
