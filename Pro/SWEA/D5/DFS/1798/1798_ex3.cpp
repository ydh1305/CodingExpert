#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

struct Data {
    int idx;
    int stime;
    int sat;
};
Data TOUR[36], HOTEL[36];

int dist[36][36];
bool visit[36];
int sol_sat;
int N, M, AIR;
int nTOUR, nHOTEL;
vector<int> route;
vector<int> sol_route;

void DFS(int cur, int day, int sat, int time, int visited) {
    if(cur == AIR && day == M && visited != 0) {
        if(sol_sat < sat) {
            sol_sat = sat;
            sol_route = route;
        }
        return;
    }
    bool tour_ok = false;
    for(int i = 0; i < nTOUR; ++i) {
        int next = TOUR[i].idx;
        int spend_time = TOUR[i].stime;
        int sat_rate = TOUR[i].sat;
        int move_time = dist[cur][next];
        if(time + spend_time + move_time > 540) continue;
        if(visit[next]) continue;
        if(cur == next) continue;
        visit[next] = true;
        tour_ok = true;
        route.push_back(next);
        DFS(next, day, sat + sat_rate, time + spend_time + move_time, visited + 1);
        route.pop_back();
        visit[next] = false;
    }

    if(!tour_ok) {
        if(day == M) {
            if(time + dist[cur][AIR] <= 540) {
                route.push_back(AIR);
                DFS(AIR, day, sat, 0, visited + 1);
                route.pop_back();
            }
        } else {
            for(int i = 0; i < nHOTEL; ++i) {
                int num = HOTEL[i].idx;
                if(time + dist[cur][num] <= 540) {
                    route.push_back(num);
                    DFS(num, day + 1, sat, 0, visited + 1);
                    route.pop_back();
                }
            }
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        cin >> N >> M;
        nTOUR = nHOTEL = sol_sat = 0;
        for(int i = 1; i < N; ++i) {
            for(int j = i + 1; j <= N; ++j) {
                int x; cin >> x;
                dist[i][j] = dist[j][i] = x;
            }
        }
        for(int i = 1; i <= N; ++i) {
            char s; cin >> s;
            if(s == 'A') AIR = i;
            if(s == 'P') {
                int x, y; cin >> x >> y;
                TOUR[nTOUR].idx = i;
                TOUR[nTOUR].stime = x;
                TOUR[nTOUR++].sat = y;
            }
            if(s == 'H') HOTEL[nHOTEL++].idx = i;
        }
        DFS(AIR, 1, 0, 0, 0);
        cout << '#' << t << ' ' << sol_sat << ' ';
        if(sol_sat) {
            for(int i = 0; i < sol_route.size(); i++)
                cout << sol_route[i] << ' ';
        }
        cout << '\n';
    }
    return 0;
}