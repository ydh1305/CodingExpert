#include <bits/stdc++.h>
using namespace std;

#define MAX 20
long long arr[MAX][MAX];
bool visit[1 << 21];
int N;
set<int> sol;

void DFS(int bits, int cnt) {
    if(visit[bits]) return;
    visit[bits] = true;
    if(cnt == N - 1) {
        for(int i = 0; i < N; i++) {
            if((bits & (1 << i)) == 0) {
                sol.insert(i + 1);
                break;
            }
        }
    }
    for(int i = 0; i < N; i++) {
        if((bits & (1 << i)) == 0) {
            long long sum = 0;
            for(int j = 0; j < N; j++) {
                if((bits & (1 << j)) == 0)
                    sum = sum + arr[i][j];
            }
            if(sum > 0)
                DFS((bits | (1 << i)), cnt + 1);
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N;
        memset(visit, false, sizeof(visit));
        for(int h = 0; h < N; h++)
            for(int w = 0; w < N; w++)
                cin >> arr[h][w];
        sol.clear();
        DFS(0, 0);
        vector<int> v;
        for(auto it = sol.begin(); it != sol.end(); it++)
            v.push_back(*it);
        sort(v.begin(), v.end());
        cout << '#' << i << ' ' << v.size() << ' ';
        for(int j = 0; j < v.size(); j++)
            cout << v[j] << ' ';
        cout << '\n';
    }
    return 0;
}