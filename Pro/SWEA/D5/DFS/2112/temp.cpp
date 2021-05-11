#include <iostream>
#include <algorithm>
 
using namespace std;
 
int f[13][20];
int c[13];
int D, W, K, ans;
 
bool chk(int x) {
    for (int i = 0; i < W; i++) {
        int A = 0, B = 0, pass = 0;
        for (int j = 0; j < D; j++) {
            if (c[j] == 0) {
                if (f[j][i] == 0) A++, B = 0;
                else B++, A = 0;
            }
            else {
                if (x == 0) A++, B = 0;
                else B++, A = 0;
            }
            if (A == K || B == K) pass = 1;
        }
        if (!pass) return false;
    }
    return true;
}
 
void solve(int pos, int cnt) {
    if (cnt >= ans) return;
 
    if (pos == D) {
        if (chk(0) && cnt < ans) ans = cnt;
        if (chk(1) && cnt < ans) ans = cnt;
        return;
    }
    c[pos] = 0;
    solve(pos + 1, cnt);
    c[pos] = 1;
    solve(pos + 1, cnt + 1);
}
 
int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        cin >> D >> W >> K;
        for (int i = 0; i < D; i++) {
            for (int j = 0; j < W; j++)
                cin >> f[i][j];
        }
        ans = K;
        solve(0, 0);
        cout << '#' << tc << ' ' << ans << '\n';
    }
}