#include <bits/stdc++.h>
using namespace std;

#define MAX 1000
int N;
int arr[MAX][MAX];
long long visit[MAX][MAX];
long long sol;

int hh[2] = { 1, 0 };
int ww[2] = { 0, 1 };

long long get_count(long long num) {
    int cnt = 0;
    while(num / 10 != 0) {
        if(!(num % 10)) cnt++;
        num = num / 10;
    }
    return cnt;
}

#if 0
long long BFS(int y, int x) {
    queue<pair<int, int>> q;
    q.push({y, x});
    visit[y][x] = 0;
    while(!q.empty()) {
        pair<int, int> data;
        data = q.front(); q.pop();
        for(int i = 0; i < 2; i++) {
            int H = data.first + hh[i];
            int W = data.second + ww[i];
            if(data.first == N - 1 && data.second == N - 1) return visit[data.first][data.second];
            if(H > N - 1 || W > N - 1) continue;
            if(arr[H][W] == 0) continue;
            long long num = arr[H][W] * arr[data.first][data.second];
            num = get_count(num);
            if(visit[H][W] > num) {
                if(num > visit[data.first][data.second]) visit[H][W] = num + visit[data.first][data.second];
                else visit[H][W] = visit[data.first][data.second];
                q.push({H, W});
            }
        }
    }
}
#endif

void DFS(int y, int x) {
    if(y == N - 1 && x == N - 1) {
        sol = min(sol, visit[y][x]);
        return;
    }
    if(sol < visit[y][x]) return;
    for(int i = 0; i < 2; i++) {
        int H = y + hh[i];
        int W = x + ww[i];
        if(H > N - 1 || W > N - 1) continue;
        if(arr[H][W] == 0) continue;
        long long num = arr[H][W] * arr[y][x];
        num = get_count(num);
        if(visit[H][W] > num) {
            if(num > visit[y][x]) visit[H][W] = num + visit[y][x];
            else visit[H][W] = visit[y][x];
            DFS(H, W);
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; scanf("%d", &T);
    for(int i = 1; i <= T; i++) {
        scanf("%d", &N);
        for(int h = 0; h < N; h++) {
            for(int w = 0; w < N; w++) {
                visit[h][w] = INT_MAX;
                scanf("%d", &arr[h][w]);
            }
        }
        sol = INT_MAX;
        visit[0][0] = 0;
        DFS(0, 0);    
        printf("#%d %lld\n", i, sol);
    }
    return 0;
}