#include <iostream>
using namespace std;

#define NULL 0
int total;
char name[31];

struct Trie {
    int child;
    bool finish;
    Trie *Node[96];

    Trie() {
        child = 0;
        finish = false;
        for(register int i = 0; i < 96; i++) Node[i] = NULL;
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
            name[idx] = '\0';
            cout << name << ' ' << (double)child * 100 / (double)total << '\n';
        }
        for(register int i = 0; i < 96; i++) {
            if(Node[i]) {
                int cur = i + 32;
                name[idx] = cur;
                Node[i]->search(idx + 1);
            }
        }
    }
};

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    string s;
    Trie *root = new Trie();
    while(true) {
        getline(cin, s);
        if(s.length() == 0) break;
        register int i = 0;
        for(; i < s.length(); i++) name[i] = s[i];
        name[i] = '\0';
        root->insert(name);
        total++;
    }
    cout << fixed;
    cout.precision(4);
    root->search(0);

    return 0;
}
