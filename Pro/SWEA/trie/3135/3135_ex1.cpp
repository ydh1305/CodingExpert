using namespace std;

#define MAX 1000000
#define NULL 0

struct trie {
    int child;
    bool finish;
    trie *Node[26];

    void insert(char *str);
    int find(char *str);
};

int idx;
trie *root, nodepool[MAX];

trie *create(void) {
    trie *newNode = &nodepool[idx++];
    newNode->child = 0;
    newNode->finish = false;
    for(int i = 0; i < 26; i++) newNode->Node[i] = NULL;
    return newNode;
}

void trie::insert(char *str) {
    child++;
    if(*str == NULL) {
        finish = true;
        return;
    }
    int cur = *str - 'a';
    if(Node[cur] == NULL) Node[cur] = create();
    Node[cur]->insert(str + 1);
}

int trie::find(char *str) {
    if(*str == NULL) return child; 
    int cur = *str - 'a';
    if(Node[cur] == NULL) return 0;
    return Node[cur]->find(str + 1);
}

void init(void) {
    idx = 0;
    root = create();
}

void insert(int buffer_size, char *buf) {
    root->insert(buf);
}

void query(int buffer_size, char *buf) {
    return root->find(buf);
}
