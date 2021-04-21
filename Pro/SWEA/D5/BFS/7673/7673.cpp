#include <bits/stdc++.h>
using namespace std;

#define MAX 1000
int N;
int arr[MAX][MAX];
long long visit[MAX][MAX];

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
            if(H == N && W == N) return visit[H][W];
            if(H > N - 1 || W > N - 1) continue;
            if(arr[H][W] == 0) continue;
            long long num = arr[H][W] * arr[data.first][data.second];
            num = get_count(num);
            if(visit[H][W] > num) {
                visit[H][W] = num;
                q.push({H, W});
            }
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
                scanf("%d", &arr[h][w]);
                visit[h][w] = INT_MAX;
            }
        }
        printf("#%d %lld\n", i, BFS(0, 0));
    }
    return 0;
}