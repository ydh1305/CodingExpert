#include <bits/stdc++.h>
using namespace std;

int C[200001], S[200001];

int comp(const pair<int, pair<int, int>> &a, const pair<int, pair<int, int>> &b) {
    if(a.second.second == b.second.second)
        return a.first < b.first;
    return a.second.second < b.second.second;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int N; cin >> N;
    pair<int, pair<int, int>> v[200001];
    for(int i = 0; i < N; i++) {
        int a, b; cin >> a >> b;
        v[i] = {i + 1, {a, b}};
    }
    sort(v, v + N, comp);
    register int s = 0;
    int sum = 0;
    for(int e = 0; e < N; e++) {
        for(; s < e && v[s].second.second < v[e].second.second; s++) {
            sum = sum + v[s].second.second;
            C[v[s].second.first] = C[v[s].second.first] + v[s].second.second;
        }
        S[v[e].first] = sum - C[v[e].second.first];
    }
    for(int i = 1; i <= N; i++)
        cout << S[i] << '\n';
    return 0;
}