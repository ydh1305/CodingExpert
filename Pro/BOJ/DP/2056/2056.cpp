#include <iostream>
#include <vector>
using namespace std;

int N, sol, total;
int dist[10001];
vector<int> v[10001];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    for(int i = 1; i <= N; ++i) {
        cin >> dist[i];
        int n; cin >> n;
        for(int j = 0; j < n; ++j) {
            int x; cin >> x;
            v[i].push_back(x);
        }
    }
    for(int i = 1; i <= N; ++i) {
        int sum = 0;
        for(int j = 0; j < v[i].size(); ++j) {
            int parent = v[i][j];
            sum = max(sum, dist[parent]);
        }
        dist[i] = sum + dist[i];
    }
    for(int i = 1; i <= N; ++i)
        total = max(total, dist[i]);
    cout << total;
    return 0;
}