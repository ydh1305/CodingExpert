#include <iostream>
using namespace std;

#define NULL 0

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
        child++;
        if(*str == '\0') {
            finish = true;
            return;
        }
        int cur = *str - 'a';
        if(Node[cur] == NULL) Node[cur] = new Trie();
        Node[cur]->insert(str + 1);
    }

    int find(char *str) {
        if(*str == '\0') return child;
        int cur = *str - 'a';
        if(Node[cur] == NULL) return 0;
        return Node[cur]->find(str + 1);
    }
};
Trie *root;

void init(void) {
    root = new Trie();
}

void insert(int buffer_size, char *buf) {
    root->insert(buf);
}

int query(int buffer_size, char *buf) {
    return root->find(buf);
}
