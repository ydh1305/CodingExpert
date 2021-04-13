#include <iostream>
#include <cstring>
#include <map>
using namespace std;

#define MAX 21
char str[MAX];
char temp[MAX];
bool visit[21];
int total;

map<string, int> m;
int map_idx;

void DFS(int n) {
    if(n == strlen(str)) {
        if(strncmp(temp, str, strlen(temp)) == 0) return;
        if (m.find(temp) == m.end()) {
            m.insert({temp, total++});
        }
        return;
    }
    for(int i = 0; str[i]; i++) {
        if(visit[i] == true) continue;
        temp[n] = str[i];
        if(strncmp(temp, str, strlen(temp)) > 0) continue;
        visit[i] = true;
        DFS(n + 1);
        visit[i] = false;
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> str;
        total = 0;
        m.clear();
        memset(temp, 0, sizeof(temp));
        memset(visit, 0, sizeof(visit));
        DFS(0);
        cout << '#' << i << ' ' << total << '\n';
    }
    return 0;
}