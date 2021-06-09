#include <iostream>
#include <cstring>
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
        for(register int i = 0; i < E; ++i) {
            int parent, child; cin >> parent >> child;
            if(!tree[parent].left) 
                tree[parent].left = child;
            else
                tree[parent].right = child;
            tree[child].parent = parent;
        }
        int cur = tree[X].parent;
        while(true) {
            visit[cur] = true;
            if(cur == 1) break;
            cur = tree[cur].parent;
        }
        cur = tree[Y].parent;
        while(true) {
            if(visit[cur]) {
                cout << '#' << t << ' ' << cur << ' ' << DFS(cur) << '\n';
                break;
            }
            cur = tree[cur].parent;
        }
    }
    return 0;
}