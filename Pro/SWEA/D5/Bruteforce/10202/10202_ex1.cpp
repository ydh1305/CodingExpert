#include <iostream>
using namespace std;

char str[3][1001];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; t++) {
        int N; cin >> N;
        for(int i = 0; i < 3; i++)
            cin >> str[i];
        int cnt = 0;
        for(int i = 0; i < N; i++) {
            if(str[0][i] == str[1][i] && str[1][i] == str[2][i]) continue;
            else if(str[0][i] == str[1][i] && str[1][i] != str[2][i]) cnt = cnt + 1;
            else if(str[0][i] != str[1][i] && str[1][i] == str[2][i]) cnt = cnt + 1;
            else if(str[0][i] == str[2][i] && str[1][i] != str[2][i]) cnt = cnt + 1;
            else cnt = cnt + 2;
        }
        cout << '#' << t << ' ' << cnt << '\n';
    }
    return 0;
}