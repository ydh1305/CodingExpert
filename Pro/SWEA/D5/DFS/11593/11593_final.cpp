#include <bits/stdc++.h>
using namespace std;

int arr[26];
long long dic[21];
long long sum;
int total;
vector<int> v;

long long factorial(int n) {
    if(n <= 1) return 1;
    if(dic[n]) return dic[n];
    dic[n] = n * factorial(n - 1);
    return dic[n];
}

void DFS(char *str, int idx) {
    if(idx == total - 1) return;
    for(int i = 0; i < v.size(); i++) {
        int cur = v[i];
        if(str[idx] - 'A' <= cur) continue;
        if(arr[cur]) {
            arr[cur]--;
            long long bottom = 1;
            for(int j = 0; j < v.size(); j++) {
                if(arr[v[j]]) {
                    bottom = bottom * factorial(arr[v[j]]);
                }
            }
            long long top = factorial(total - (idx + 1));
            sum = sum + (top / bottom);
            arr[cur]++;
        }
    }
    arr[str[idx] - 'A']--;
    DFS(str, idx + 1);
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        char s[21]; cin >> s;
        sum = 0; 
        v.clear();
        memset(arr, 0, sizeof(arr));
        total = strlen(s);
        for(int j = 0; s[j]; j++) {
            int idx = s[j] - 'A';
            if(!arr[idx]) v.push_back(idx);
            arr[idx]++;
        }
        DFS(s, 0);
        cout << "#" << i << ' ' << sum << '\n';
    }
    return 0;
} 