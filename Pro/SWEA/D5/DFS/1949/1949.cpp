#include <bits/stdc++.h>
using namespace std;

int arr[9][9];
bool visit[9][9];
int N, K, sol;

int hh[4] = { -1, 1, 0, 0 };
int ww[4] = { 0, 0, -1, 1 };

void DFS(int h, int w, bool cut, int prev, int cnt) {
    visit[h][w] = true;
    if(sol < cnt) sol = cnt;
    for(int i = 0; i < 4; i++) {
        int H = h + hh[i];
        int W = w + ww[i];
        if(H < 0 || W < 0 || H > N - 1 || W > N - 1) continue;
        if(!cut) {
            if(arr[h][w] > arr[H][W] && !visit[H][W])
                DFS(H, W, cut, arr[H][W], cnt + 1);
            else {
                if(arr[h][w] > arr[H][W] - K && !visit[H][W])
                    DFS(H, W, true, arr[h][w] - 1, cnt + 1);
            }
        }
        else {
            if(prev > arr[H][W] && !visit[H][W])
                DFS(H, W, cut, arr[H][W], cnt + 1);
        }
    }
    visit[h][w] = false;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N >> K;
        int max = 0;
        sol = 0;
        vector<pair<int, int>> v;
        for(int h = 0; h < N; h++) {
            for(int w = 0; w < N; w++) {
                cin >> arr[h][w];
                if(max < arr[h][w]) {
                    v.clear();
                    v.push_back({h, w});
                    max = arr[h][w];
                } else if(max == arr[h][w]) v.push_back({h, w});
            }
        }
        for(int j = 0; j < v.size(); j++)
            DFS(v[j].first, v[j].second, false, 20, 1);
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}