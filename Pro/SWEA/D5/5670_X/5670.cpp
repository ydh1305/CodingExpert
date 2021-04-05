#include <iostream>
using namespace std;

#define MAX 20001

int check1[MAX];
int check2[MAX];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int cnt;
    int T; cin >> T;
    for(int i = 0; i < T; i++) {
        int G, N;
        cin >> G >> N;
        cnt = 0;
        for(int j = 0; j < MAX; j++) check1[j] = 0;
        for(int j = 0; j < MAX; j++) check2[j] = 0;
        for(int j = 0; j < N; j++) {
            int x1, x2, y1, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            int m = (y2 - y1) / (x2 - x1);
            int y = (m * x1 * -1) + y1;
            if(!check1[m] && !check2[y]) {
                check1[m] = 1; check2[y] = 1;
                cnt++;
            }
        }
        cnt *= 2;
        int sol = 0;
        if(cnt >= G) sol = 0; 
        else sol = G - cnt;
        cout << '#' << i + 1 << ' ' << sol << '\n';
    }

    return 0;
}
