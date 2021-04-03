#include <iostream>
using namespace std;

#define NULL 0

char temp[6];
int name_idx;

struct Word {
    char word[6];
    Word &operator =(const Word &org) {
        int i = 0;
        for(; org.word[i]; i++)
            word[i] = org.word[i];
        word[i] = 0;
        return * this;
    }

    bool operator <(const Word &other) const {
        int i = 0;
        for(; word[i]; i++) {
            if(word[i] != other.word[i])
                return word[i] < other.word[i];
        }
        return word[i] < other.word[i];
    }
};
Word name[1000000];
Word tmp[1000000];

void merge(Word *arr, int s, int m, int e) {
    int i = s, j = m + 1, k = s;

    while(i <= m && j <= e) {
        if(arr[j] < arr[i]) {
            tmp[k] = arr[j];
            j++;
        }
        else {
            tmp[k] = arr[i];
            i++;
        }
        k++;
    }
    if(i > m) {
        for(int t = j; t <= e; t++) {
            tmp[k] = arr[t];
            k++;
        }
    }
    else {
        for(int t = i; t <= m; t++) {
            tmp[k] = arr[t];
            k++;
        }
    }

    for(int t = s; t <= e; t++) {
        arr[t] = tmp[t];
    }
}

void merge_sort(Word *arr, int s, int e) {
    if(s < e) {
        int m = (s + e) / 2;
        merge_sort(arr, s, m);
        merge_sort(arr, m + 1, e);
        merge(arr, s, m, e);
    }
}

struct Trie {
    int child;
    bool finish;
    Trie *Node[63];

    Trie() {
        child = 0;
        finish = false;
        for(int i = 0; i < 63; i++) Node[i] = NULL;
    }
    void insert(char *str) {
        child++;
        if(*str == '\0') {
            finish = true;
            return;
        }
        int cur = *str - 'A';
        if(Node[cur] == NULL) Node[cur] = new Trie();
        Node[cur]->insert(str + 1);
    }
    void search(int idx) {
        if(finish == true) {
            temp[idx] = '\0';
            int i = 0;
            for(; temp[i]; i++)
                name[name_idx].word[i] = temp[i];
            name[name_idx++].word[i] = '\0';
        }
        for(int i = 62; i >= 0; i--) {
            if(Node[i]) {
                int cur = i + 'A';
                temp[idx] = cur;
                Node[i]->search(idx + 1);
            }
        }
    }
    void remove(char *str) {
        child--;
        if(*str == '\0') {
            finish = false;
        }
        else {
            int cur = *str - 'A';
            Node[cur]->remove(str + 1);
            if(!child) {
                delete Node[cur];
                Node[cur] = NULL;
            }
        }
    }
};

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    Trie *root = new Trie();
    int N; cin >> N;
    char s1[6], s2[6];
    for(register int i = 0; i < N; i++) {
        cin >> s1 >> s2;
        if(s2[0] == 'e') root->insert(s1); 
        if(s2[0] == 'l') root->remove(s1); 
    }
    root->search(0);
    merge_sort(name, 0, name_idx - 1);
    for(register int i = 0; i < name_idx; i++)
        cout << name[i].word << '\n';

    return 0;
}
