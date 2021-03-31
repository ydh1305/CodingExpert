#include <iostream>
using namespace std;

#define NULL 0

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
    ios::sync_with_stdio(0);
    cin.tie(0);
    Trie *root = new Trie();
    Trie *froot = new Trie();
    int N, M;
    cin >> N >> M;
    for(int i = 0; i < N; i++) {
        cin >> tree;
        root->insert(tree);
    }
    for(int i = 0; i < M; i++) {
        cin >> tree;
        if(root->find(tree)) total++, froot->insert(tree);
    }
    cout << total << endl;
    froot->search(0);

    return 0;
}
