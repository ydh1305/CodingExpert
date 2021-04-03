#include <iostream>
using namespace std;

#define NULL 0
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
        child++;
        if(*str == '\0') {
            finish = true;
            return;
        }
        int cur = *str - 'a';
        if(Node[cur] == NULL) Node[cur] = new Trie();
        Node[cur]->insert(str + 1);
    }
    int find(char *str, int cnt) {
        if(*str == '\0' || child == 1) return cnt;
        int cur = *str - 'a';
        return Node[cur]->find(str + 1, cnt + 1);
    }
};

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    Trie *root = new Trie();
    int N; cin >> N;
    char temp[10][10];
    for(int i = 0; i < N; i++) {
        cin >> temp[i]; root->insert(temp[i]); 
    }
    for(int i = 0; i < N; i++) {
        total = total + root->find(temp[i], 0);
    }
    cout << total << endl;

    return 0;
}
