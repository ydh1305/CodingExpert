#include <bits/stdc++.h>
using namespace std;

long long arr[21][21];
long long S[21];
bool visit[21];
bool check[21];
int cnt, N;
vector<int> v;
vector<int> v1;
set<int> sol;

void DFS(void) {
    int num = 0, temp = 0;
    for(int j = 1; j <= N; j++) {
        if(S[j] > 0) {
            num++;
            if(num == 1) temp = j;
        }
    }
    if(num == 1) sol.insert(temp);
    for(int i = 0; i < v.size(); i++) {
        if(visit[v[i]]) continue;
        visit[v[i]] = true;
        for(int j = 1; j <= N; j++) {
            S[j] = S[j] - arr[v[i]][j];
            S[j] = S[j] + arr[j][v[i]];
        }
        DFS();
        for(int j = 1; j <= N; j++) {
            S[j] = S[j] + arr[v[i]][j];
            S[j] = S[j] - arr[j][v[i]];
        }
        visit[v[i]] = false;
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> N;
        sol.clear();
        for(int i = 1; i <= N; i++) {
            S[i] = 0;
            check[i] = false;
        }
        for(int h = 1; h <= N; h++) {
            for(int w = 1; w <= N; w++) {
                cin >> arr[h][w];
                if(!arr[h][w] || h == w) continue;
                S[h] = S[h] + (arr[h][w] * -1);
                S[w] = S[w] + arr[h][w];
            }
        }
        v.clear();
        for(int j = 1; j <= N; j++) {
            if(S[j] <= 0) v.push_back(j);
        }
        DFS();
        v1.clear();
        for(auto it = sol.begin(); it != sol.end(); it++) {
            v1.push_back(*it);
        }
        sort(v1.begin(), v1.end());
        cout << '#' << i << ' ' << v1.size() << ' ';
        for(int j = 0; j < v1.size(); j++) 
            cout << v1[j] << ' ';
        cout << '\n';
    }
    return 0;
}