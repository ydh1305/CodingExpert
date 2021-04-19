#include <bits/stdc++.h>
using namespace std;

int check[21];
int N, M, sol;

void DFS(int n, int val) {
    if(n == N + 1) {
        sol++;
        return;
    }
    DFS(n + 1, val);
    DFS(n + 1, val);
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    sol = 0;
    DFS(1, 0);
    cout << sol << '\n';
    return 0;
}