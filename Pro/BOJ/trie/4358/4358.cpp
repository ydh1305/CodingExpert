#include <iostream>
using namespace std;

#define NULL 0

int total;
char tree[31];

struct trie {
    int child;
    bool finish;
    trie *Node[96];

    trie() {
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
        if(Node[cur] == NULL) Node[cur] = new trie();
        Node[cur]->insert(str + 1);
    }
    void searchall(int idx) {
        if(finish == true) {
            tree[idx] = '\0';
            printf("%s %.4lf\n", tree, (double)child * 100 / (double)total);
        }
        for(int i = 0; i < 96; i++) {
            if(Node[i]) {
                int cur = i + 32;
                tree[idx] = cur;
                Node[i]->searchall(idx + 1);
            }
        }
    }
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    trie *root = new trie();
    string s;
    while(true) {
        getline(cin, s);
        if(s.length() == 0) break;
        for(int i = 0; i < s.length(); i++) tree[i] = s[i];
        tree[s.length()] = '\0';
        root->insert(tree);
        total++;
    }
    root->searchall(0);
}
