#include <iostream>
using namespace std;

struct Trie {
    int child;
    bool finish;
    Trie *Node[26];

    Trie() {
        child = 0;
        finish = false;
        for(int i = 0; i < 26; i++)
            Node[i] = 0;
    }
    void insert(char *str) {
        if(*str == '\0') {
            finish = true;
            return;
        }
        int cur = *str - 'A';
        if(Node[cur] == NULL) Node[cur] = new Trie();
        Node[cur]->insert(str + 1);
    }
    void search(char *str) {
    }
};

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);


    return;
}