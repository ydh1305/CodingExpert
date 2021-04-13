#include <bits/stdc++.h>
#include<vector>
using namespace std;

#define MAX 1001
int sum[MAX][MAX];
int sol;

int DFS(int n, int x1, int y1, int x2, int y2) {
    int total = sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y2 - 1] + sum[x1 - 1][y1 - 1];
    int area = (x2 - x1 + 1) * (x2 - x1 + 1);
    int m = n / 2;
    if(total == area) {
        if(sol < area) sol = area;
    } else {
        
    }
}

int solution(vector<vector<int>> board) {
    int H = board.size(); int W = board[0].size();
    memset(sum, 0, sizeof(sum));
    sol = 0;
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            if(i == 0 && j == 0) sum[0][0] = board[0][0];
            else sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + board[i][j];
        }
    }
    if(H > W)
        DFS(H, 0, 0, H - 1, W - 1);
    else
        DFS(W, 0, 0, H - 1, W - 1);
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    //vector<vector<int>> v(1000, vector<int>(1000));
    vector<vector<int>> v({
        vector<int>({0, 1, 1, 1}),
        vector<int>({1, 1, 1, 1}),
        vector<int>({1, 1, 1, 1}),
        vector<int>({0, 0, 1, 0})
    });
    solution(v);
    return 0;
}