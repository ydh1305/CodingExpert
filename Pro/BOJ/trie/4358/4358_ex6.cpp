#include <iostream>
using namespace std;

#define NULL 0

char name[31];
int total;

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
            name[idx] = '\0';
            cout << name << ' ' << (double)child * 100 / (double)total << '\n';
        }
        for(int i = 0; i < 96; i++) {
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
    Trie *root = new Trie();
    string s;
    while(true) {
        getline(cin, s);
        if(s.length() == 0) break;
        int i = 0;
        for(; i < s.length(); i++)
            name[i] = s[i];
        name[i] = '\0';
        root->insert(name);
        total++;
    }
    cout << fixed;
    cout.precision(4);
    root->search(0);
    return 0;
}