#include <iostream>
using namespace std;

typedef struct Node {
    int data;
    Node *next;
} Node;

struct Stack {
    Node *head, *tail;
};
Stack st[1001];
int dist[1001][1001];
bool visit[1001];
long long sol;

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

void DFS(int s, int cur, long long len) {
    Node *Cur = NULL;
    visit[cur] = true;
    for(Cur = st[cur].head; Cur != NULL; Cur = Cur->next) {
        if(!visit[Cur->data]) {
            int e = Cur->data;
            dist[s][e] = dist[cur][e] + len;
            if(s < e) sol = sol + dist[s][e];
            DFS(s, e, dist[s][e]);
        }
    }
    visit[cur] = false;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int N; cin >> N;
        for(int i = 1; i <= N; ++i) 
            st[i].head = st[i].tail = NULL;
        for(int i = 0; i < N - 1; ++i) {
            int x, y, d; cin >> x >> y >> d;
            dist[x][y] = dist[y][x] = d;
            push(x, y); push(y, x);
        }
        sol = 0;
        for(int i = 1; i <= N; i++)
            DFS(i, i, 0);
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}