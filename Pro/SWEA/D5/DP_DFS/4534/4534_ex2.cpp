#include <iostream>
using namespace std;

#define MOD 1000000007
#define WHITE 0
#define BLACK 1

typedef struct Node {
    int data;
    Node *next;
} Node;

struct Stack {
    Node *head, *tail;
};
Stack st[100001];

long long dp[100001][2];
bool visit[100001];

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

long long DFS(int n, int c) {
    long long& sol = dp[n][c];
    if(sol != -1) return sol;
    sol = 1;
    visit[n] = true;
    Node *Cur = NULL;
    for(Cur = st[n].head; Cur != NULL; Cur = Cur->next) {
        int next = Cur->data;
        if(visit[next]) continue;
        if(c == WHITE)
            sol = (sol * (DFS(next, WHITE) + DFS(next, BLACK))) % MOD;
        else 
            sol = (sol * DFS(next, WHITE)) % MOD;
    }
    visit[n] = false;
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int N; cin >> N;
        for(int i = 1; i <= N; ++i) {
            st[i].head = st[i].tail = 0;
            dp[i][0] = dp[i][1] = -1;
        }
        for(register int i = 1; i < N; ++i) {
            int x, y; cin >> x >> y;
            push(x, y); push(y, x);
        }
        cout << '#' << t << ' ' << (DFS(1, WHITE) + DFS(1, BLACK)) % MOD << '\n';
    }
    return 0;
}