#include <iostream>
using namespace std;

#define MAX (30 * 10001)
#define NULL 0

struct trie {
    int child;
    bool finish;
    trie *Node[96];

    void insert(char *str);
    int sort(trie *N, char *str, int _idx);
};

int idx;
int total_cnt;
trie *root, nodepool[MAX];

trie *create(void) {
    trie *newNode = &nodepool[idx++];
    newNode->child = 0;
    newNode->finish = false;
    for(int i = 0; i < 96; i++) newNode->Node[i] = NULL;
    return newNode;
}

void trie::insert(char *str) {
    child++;
    if(*str == '\0') {
        finish = true;
        return;
    }
    char cur = *str - 32;
    if(Node[cur] == NULL) Node[cur] = create();
    Node[cur]->insert(str + 1);
}

int trie::sort(trie *N, char *str, int _idx) {
    if(N->finish == true) {
        str[_idx] = '\0';
//        printf("%d %d\n", child, total_cnt);
        printf("%s %.4lf\n", str, (double)child * 100 / (double)total_cnt); 
    }
    for(int i = 0; i < 96; i++) {
        if(N->Node[i] != NULL) {
            char cur = i + 32;
            str[_idx] = cur;
            N->sort(N->Node[i], str, _idx + 1);
        }
    }
}

void init(void) {
    idx = 0;
    root = create();
}

int main(void) {
    string s;
    init();
    while(true) {
        char temp[31] = { 0, };
        //cin.getline(temp, 30);
        getline(cin, s);
        if(s.length() == 0) break;
        for(int i = 0; i < s.length(); i++) temp[i] = s[i];
        temp[s.length()] = '\0';
        root->insert(temp);
        total_cnt++;
    }
    for(int i = 0; i < 96; i++) {
        if(root->Node[i] != NULL) {
            //char temp[30] = { NULL, };
            char temp[31] = { 0, };
            temp[0] = i + 32;
            root->sort(root->Node[i], temp, 1);
        }
    }

    return 0;
}
