#include <iostream>
using namespace std;

template <typename T>
class _queue {
public:
    struct Node {
        T v;
        Node *next;
        Node(T v):v(v), next(0) {}
        Node() {}
    };
    Node *head;
    Node *tail;
    int s;

    _queue() {
        head = tail = 0;
        s = 0;
    }
    void push(T v) {
        T *temp = new Node(v);
    }
};

#define MAX 2001
char map[MAX][MAX]
bool visit[MAX][MAX];
string sol;
int H, W;

string BFS(int y, int x) {

}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> H >> W;
        for(int j = 0; j < H; j++) cin >> map[j];
        cout << '#' << i << ' ' << BFS(0, 0) << '\n';
    }

    return 0;
}
