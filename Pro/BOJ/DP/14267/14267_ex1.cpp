#include <iostream>
using namespace std;

int dp[100001];

typedef struct Node {
    int data;
    Node *next;
} Node;

struct Stack {
    Node *head, *tail;
};
Stack st[100001];

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

void DFS(int n, int m) {
    dp[n] = dp[n] + m;
    for(Node *Cur = st[n].head; Cur != NULL; Cur = Cur->next) {
        DFS(Cur->data, dp[n]);
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int N, M; cin >> N >> M;
    for(int i = 1; i <= N; ++i) {
        int x; cin >> x;
        if(i == 1) continue;
        push(x, i);
    }
    for(register int i = 0; i < M; ++i) {
        int a, b; cin >> a >> b;
        dp[a] = dp[a] + b;
    }
    DFS(1, 0);
    for(int i = 1; i <= N; ++i)
        cout << dp[i] << ' ';
    cout << '\n';
    return 0;
}