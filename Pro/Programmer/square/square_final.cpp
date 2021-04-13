#include <iostream>
#include <vector>
using namespace std;

int solution(vector<vector<int>> board) {
    int sol = 0;
    int H = board.size(); int W = board[0].size();
    vector<vector<int>> map(H + 1, vector<int>(W + 1, 0));

    for(int h = 0; h < H; h++)
        for(int w = 0; w < W; w++) 
            map[h + 1][w + 1] = board[h][w];

    for(int h = 1; h <= H; h++) {
        for(int w = 1; w <= W; w++) {
            if(map[h][w]) {
                map[h][w] = min(map[h - 1][w], min(map[h - 1][w - 1], map[h][w - 1])) + 1;
                if(sol < map[h][w]) sol = map[h][w];
            }
        }
    }
    return sol * sol;
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