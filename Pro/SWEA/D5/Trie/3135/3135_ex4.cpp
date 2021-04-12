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
        if(*str == '\0') {
            return child;
        }
        int cur = *str - 'a';
        if(Node[cur] == NULL) return 0;
        Node[cur]->find(str + 1);
    }
};

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        Trie *root = Trie();
        int N; cin >> N;
        for(int j = 0; j < N; j++) {
            int n; cin >> n;
            char s[11]; cin >> s;
            if(n == 1) root->insert(s);
            if(n == 2) root->find(s);
        }
    }

    return 0;
}