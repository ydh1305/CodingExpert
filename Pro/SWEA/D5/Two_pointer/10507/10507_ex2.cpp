#include <iostream>
#include <cstring>
using namespace std;

int arr[1000001];
bool visit[1000001];
int N, P;

int solve(void) {
    int s = 1, e = 1;
    int end = arr[N - 1];
    int cnt = 0, sol = P + 1;
    while(e <= end) {
        if(visit[e]) {
            e++;
            cnt++;
        } else {
            if(!P) {
                if(!visit[s]) P++;
                s++;
                cnt--;
            } else {
                P--;
                e++;
                cnt++;
            }
        }
        if(sol < cnt) sol = cnt;
    }
    return sol;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; t++) {
        cin >> N >> P;
        memset(visit, false, sizeof(visit));
        for(int i = 0; i < N; i++) {
            cin >> arr[i];
            if(!visit[arr[i]]) 
                visit[arr[i]] = true;
        }
        cout << '#' << t << ' ' << solve() << '\n';
    }
    return 0;
}