#include <iostream>
using namespace std;

int map[20][20];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int N, X; cin >> N >> X;
        for(int h = 0; h < N; h++)
            for(int w = 0; w < N; w++)
                cin >> map[h][w];
        int sol = 0;
        for(int h = 0; h < N; h++) {
            int s = 0, e = 0;
            while(e < N) {
                while((map[h][s] == map[h][e]) && e < N) e++;
                if(e == N) {
                    sol++;
                    break;
                }
                if(map[h][s] + 1 == map[h][e]) {
                    if(e - s >= X) s = e;
                    else break;
                }
                else if(map[h][s] - 1 == map[h][e]) {
                    s = e - 1;
                    while((map[h][e] == map[h][e + 1]) && e + 1 != N) e++;
                    if(e - s >= X) {
                        if(s + X + 1 <= e) s = s + X + 1;
                        else s = e;
                    }
                    else break;
                } else break;
            }
        }
        for(int w = 0; w < N; w++) {
            int s = 0, e = 0;
            while(e < N) {
                while(map[s][w] == map[e][w] && e < N) e++;
                if(e == N) {
                    sol++;
                    break;
                }
                if(map[s][w] + 1 == map[e][w]) {
                    if(e - s >= X) s = e;
                    else break;
                }
                else if(map[s][w] - 1 == map[e][w]) {
                    s = e - 1;
                    while((map[e][w] == map[e + 1][w]) && e + 1 != N) e++;
                    if(e - s >= X) {
                        if(s + X + 1 <= e) s = s + X + 1;
                        else s = e;
                    }
                    else break;
                } else break;
            }
        }
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}