#include <iostream>
using namespace std;

#define NULL 0

int total;
char tree[31];

struct Trie {
    int child;
    bool finish;
    Trie *Node[96];

    Trie() {
        child = 0;
        finish = false;
        for(int i = 0; i < 96; i++) Node[i] = NULL;
    }
    void insert(char *str) {
        if(*str == '\0') {
            child++;
            finish = true;
            return;
        }
        int cur = *str - 32;
        if(Node[cur] == NULL) Node[cur] = new Trie();
        Node[cur]->insert(str + 1);
    }
    void search(int idx) {
        if(finish == true) {
           tree[idx] = '\0'; 
           printf("%s %.4lf\n", tree, (double)child * 100 / (double)total);
        }
        for(int i = 0; i < 96; i++) {
            if(Node[i]) {
                int cur = i + 32;
                tree[idx] = cur;
                Node[i]->search(idx + 1);
            }
        }
    }
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    Trie *root = new Trie();
    string s;
    while(true) {
        getline(cin, s);
        if(s.length() == 0) break;
        for(int i = 0; i < s.length(); i++) tree[i] = s[i];
        tree[s.length()] = '\0';
        root->insert(tree);
        total++;
    }
    root->search(0);
}
