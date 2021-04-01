#include <iostream>
using namespace std;

#define NULL 0

char name[6];

struct Trie {
    int child;
    int finish;
    Trie *Node[63];

    Trie() {
        child = 0;
        finish = 0;
        for(int i = 0; i < 63; i++) Node[i] = NULL;
    }

    void insert(char *str) {
        child++;
        if(*str == '\0') {
            finish++;
            return;
        }
        int cur = *str - 65;
        if(Node[cur] == NULL) Node[cur] = new Trie();
        //cout << *str << ' ' << child << endl;
        Node[cur]->insert(str + 1);
    }

    void search(int idx) {
        if(finish >= 1) {
            name[idx] = '\0';
            cout << name << '\n';
        }
        for(int i = 62; i >= 0; i--) {
            if(Node[i]) {
                //int cur = i + 65;
                char cur = i + 65;
                //cout << cur << ' ' << child << endl;
                name[idx] = cur;
                Node[i]->search(idx + 1);
            }
        }
    }
    void remove(char *str) {
        //cout << child << ' ' << *str << " remove" << endl;
        int cur = *str - 65;
        if(*str == '\0') {
            finish--;
        }
        else {
            Node[cur]->remove(str + 1);
            child--;
            if(!child) {
                Node[cur] = NULL;
                delete Node[cur];
            }
        }
#if 0
        if(!child) {
            //cout << *str << " delete" << endl;
            Node[cur] = NULL;
            delete Node[cur];
        }
#endif
    }
};

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    Trie *root = new Trie();
    int N; cin >> N;
    for(int i = 0; i < N; i++) {
        char s1[6], s2[6];
        cin >> s1 >> s2;
        if(s2[0] == 'e') root->insert(s1);
        if(s2[0] == 'l') root->remove(s1); 
    }
    root->search(0);

    return 0;
}
