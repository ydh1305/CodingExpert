#include <iostream>
#include <algorithm>
using namespace std;

#define INF 987654321

struct data {
    int h;
    int w;
    int d;
};
struct data P[10], S[2];

int map[10][10];
int st1[10], st2[10];
bool visit[10];
int P_cnt, S_cnt, sol;

int dist(int n, int m) {
    return abs(P[n].h - S[m].h) + abs(P[n].w - S[m].w);
}

int solve(void) {
    int st1_cnt = 0, st2_cnt = 0;
    for(int i = 0; i < P_cnt; i++) {
        if(visit[i]) st1[st1_cnt++] = dist(i, 0) + 1;
        else st2[st2_cnt++] = dist(i, 1) + 1;
    }
    sort(st1, st1 + st1_cnt);
    sort(st2, st2 + st2_cnt);
    for(int i = 0; i < st1_cnt; i++) {
        if(i < 3) st1[i] = st1[i] + S[0].d;
        else {
            if(st1[i - 3] > st1[i]) st1[i] = st1[i - 3] + S[0].d;
            else st1[i] = st1[i] + S[0].d;
        }
    }
    for(int i = 0; i < st2_cnt; i++) {
        if(i < 3) st2[i] = st2[i] + S[1].d;
        else {
            if(st2[i - 3] > st2[i]) st2[i] = st2[i - 3] + S[1].d;
            else st2[i] = st2[i] + S[1].d;
        }
    }
    return max(st1[st1_cnt - 1], st2[st2_cnt - 1]);
}

void DFS(int n) {
    if(n == P_cnt) {
        int ret = solve();
        if(sol > ret) sol = ret;
        return;
    }
    visit[n] = true;
    DFS(n + 1);
    visit[n] = false;
    DFS(n + 1);
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int N; cin >> N;
        P_cnt = S_cnt = 0;
        for(int h = 0; h < N; h++) {
            for(int w = 0; w < N; w++){
                cin >> map[h][w];
                if(map[h][w] == 1)
                    P[P_cnt++] = { h, w, 0 };
                else if(map[h][w] > 1)
                    S[S_cnt++] = { h, w, map[h][w] };
            }
        }
        sol = INF;
        DFS(0);
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}