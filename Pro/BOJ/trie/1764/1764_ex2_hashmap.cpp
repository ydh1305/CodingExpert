#include <iostream>
using namespace std;

#define HASH_SIZE 1000000
#define PN 23
#define NULL 0
    
char temp[21];

struct HashMap {
    char name[HASH_SIZE][21];
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
        name[name_idx][i] = '\0';

        unsigned int key = get_key(str);
        int& h_size = hash_table[key][0];
        hash_table[key][++h_size] = name_idx;
        name_idx++;
        return name_idx - 1;
    }
};
HashMap hm;

struct Trie {
    bool finish;
    Trie *Node[26];

    Trie() {
        finish = false;
        for(int i = 0; i < 26; i++) Node[i] = NULL;
    }
    void insert(char *str) {
        if(*str == '\0') {
            finish = true;
            return;
        }
        int cur = *str - 'a';
        if(Node[cur] == NULL) Node[cur] = new Trie();
        Node[cur]->insert(str + 1);
    }
    void search(int idx) {
        if(finish == true) {
            temp[idx] = '\0';            
            cout << temp << '\n';
        }
        for(int i = 0; i < 26; i++) {
            if(Node[i]) {
                int cur = i + 'a';
                temp[idx] = cur;
                Node[i]->search(idx + 1);
            } 
        }
    }
};

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    Trie *root = new Trie();

    int N, M;
    int idx, total = 0;
    cin >> N >> M;
    for(register int i = 0; i < N; i++) {
        cin >> temp; hm.insert(temp);
    }
    for(register int i = 0; i < M; i++) {
        cin >> temp; 
        idx = hm.contain(temp);
        if(idx != -1) {
            root->insert(temp);
            total++;
        }
    }
    cout << total << '\n';
    root->search(0);
    
    return 0;
}
