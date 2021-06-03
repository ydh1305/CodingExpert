#include <iostream>
#include <cstring>
using namespace std;

typedef struct Node {
    int data;
    Node *next;
} Node;

struct Stack {
    Node *head, *tail;
};
Stack st[501];
bool visit[501];
bool check[501];
int sol;

void push(int n, int m) {
    Node *New = new Node;
    New->data = m;
    New->next = NULL;
    if(st[n].head == NULL && st[n].tail == NULL)
        st[n].head = st[n].tail = New;
    else {
        st[n].tail->next = New;
        st[n].tail = New;
   }
}

void DFS(int n, int len) {
    if(len > 2) return;
    Node *cur = NULL;
    visit[n] = true;
    if(!check[n]) {
        check[n] = true;
        sol = sol + 1;
    }
    for(cur = st[n].head; cur != NULL; cur = cur->next) {
        if(!visit[cur->data])
            DFS(cur->data, len + 1);
    }
    visit[n] = false;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int N, M; cin >> N >> M;
        for(int i = 1; i <= N; ++i)
            st[i].head = st[i].tail = NULL;
        memset(check, false, sizeof(check));
        for(int i = 1; i <= M; ++i) {
            int a, b; cin >> a >> b;
            push(a, b); push(b, a);
        }
        sol = 0;
        check[1] = true;
        DFS(1, 0);
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}