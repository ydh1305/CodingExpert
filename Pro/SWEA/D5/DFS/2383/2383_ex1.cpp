#include <iostream>
#include <algorithm>
using namespace std;

struct People {
    int h;
    int w;
};
People P[10];

struct Stair {
    int h;
    int w;
    int d;
};
Stair S[2];

int map[10][10];
bool visit[10];
int nP, nS, sol;

int dist(int n, int m) {
    return abs(P[n].h - S[m].h) + abs(P[n].w - S[m].w);
}

int check(void) {   
    int S1[10] = { 0, }, S2[10] = { 0, };
    int nS1 = 0, nS2 = 0;
    for(int i = 0; i < nP; i++) {
        if(visit[i]) S1[nS1++] = dist(i, 0) + 1;
        else S2[nS2++] = dist(i, 1) + 1;
    }
    sort(S1, S1 + nS1);
    sort(S2, S2 + nS2);
    for(int i = 0; i < nS1; i++) {
        if(i < 3) S1[i] = S1[i] + S[0].d;
        else {
            if(S1[i - 3] > S1[i]) S1[i] = S1[i - 3] + S[0].d;
            else S1[i] = S1[i] + S[0].d; 
        }
    }
    for(int i = 0; i < nS2; i++) {
        if(i < 3) S2[i] = S2[i] + S[1].d;
        else {
            if(S2[i - 3] > S2[i]) S2[i] = S2[i - 3] + S[1].d;
            else S2[i] = S2[i] + S[1].d; 
        }       
    }
    return max(S1[nS1 - 1], S2[nS2 - 1]);
}

void DFS(int n) {
    sol = min(sol, check());
    for(int i = n; i < nP; i++) {
        if(visit[i]) continue;
        visit[i] = true;
        DFS(i + 1);
        visit[i] = false;
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        int N; cin >> N;
        nP = nS = 0;
        for(int h = 0; h < N; h++) {
            for(int w = 0; w < N; w++) {
                cin >> map[h][w];
                if(map[h][w] == 1) P[nP++] = { h, w };
                else if(map[h][w] > 1) S[nS++] = { h, w, map[h][w] };
            }
        }
        sol = 987654321;
        DFS(0);
        cout << '#' << t << ' ' << sol << '\n';
    }
    return 0;
}