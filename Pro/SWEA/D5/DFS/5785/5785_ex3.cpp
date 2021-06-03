#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <vector>
using namespace std;

long long map[20][20];
bool visit[1 << 21];
set<int> sol;
int order[21];
int N;

void DFS(int bits, int n) {
    if(visit[bits]) return;
    visit[bits] = true;
    if(n == N - 1) {
        for(int i = 0; i < N; ++i) {
            if((bits & (1 << i)) == 0) {
                sol.insert(i + 1);
                break;
            }
        }
    }
    for(int i = 0; i < N; ++i) {
        if((bits & (1 << i)) == 0) {
            long long sum = 0;
            for(int j = 0; j < N; ++j) {
                if((bits & (1 << j)) == 0) {
                    sum = sum + map[i][j];
                }
            }
            if(sum > 0)
                DFS((bits | (1 << i)), n + 1);
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N;
        for(int h = 0; h < N; ++h)
            for(int w = 0; w < N; ++w)
                cin >> map[h][w];
        sol.clear();
        for(register int i = 0; i < (1 << N); ++i)
            visit[i] = 0;
        DFS(0, 0);
        int n;
        int idx = 0;
        for(auto n : sol)
            order[idx++] = n;
        sort(order, order + idx);
        cout << '#' << t << ' ' << idx << ' ';
        for(int i = 0; i < idx; ++i)
            cout << order[i] << ' ';
        cout << '\n';
    }
    return 0;
}