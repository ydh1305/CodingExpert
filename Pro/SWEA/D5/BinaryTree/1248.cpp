#include <iostream>
using namespace std;

struct Tree {
    int parent, left, right;
};
Tree tree[10001];
bool visit[10001];

int V, E, X, Y;

int DFS(int idx) {
    int sol = 1;
    if(tree[idx].left)
        sol = sol + DFS(tree[idx].left);
    if(tree[idx].right)
        sol = sol + DFS(tree[idx].right);
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> V >> E >> X >> Y;
        for(int i = 1; i <= V; ++i) {
            tree[i].parent = tree[i].left = tree[i].right = 0;
            visit[i] = false;
        }
        for(int i = 0; i < E; ++i) {
            int parent, child; cin >> parent >> child;
            if(!tree[parent].left) 
                tree[parent].left = child;
            else
                tree[parent].right = child;
            tree[child].parent = parent;
        }
        for(int cur = tree[X].parent; cur != NULL; cur = tree[cur].parent)
            visit[cur] = true;
        for(int cur = tree[Y].parent; cur != NULL; cur = tree[cur].parent) {
            if(visit[cur]) {
                cout << '#' << t << ' ' << cur << DFS(cur) << '\n';
                break;
            }
        }
    }
    return 0;
}