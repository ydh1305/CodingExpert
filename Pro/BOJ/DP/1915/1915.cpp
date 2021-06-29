#include <iostream>
using namespace std;

int map[1001][1001]; 
int H, W;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> H >> W;
    char tmp[1001];
    for(int i = 1; i <= H; ++i) {
        cin >> tmp;
        for(int j = 0; tmp[j]; ++j)
            map[i][j + 1] = tmp[j] - '0';
    }
    int sol = 0;
    for(int h = 1; h <= H; ++h) {
        for(int w = 1; w <= W; ++w) {
            if(map[h][w]) {
                map[h][w] = min(map[h - 1][w], min(map[h - 1][w - 1], map[h][w - 1])) + 1;
                if(sol < map[h][w]) sol = map[h][w];
            }
        }
    }
    cout << sol * sol << '\n';
    return 0;
}