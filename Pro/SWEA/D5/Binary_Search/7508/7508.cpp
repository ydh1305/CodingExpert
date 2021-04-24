#include <bits/stdc++.h>
using namespace std;

#define MAX 100000
int A[50];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for(int i = 1; i <= T; i++) {
        int N; cin >> N;
        priority_queue<int> pq;
        for(int j = 0; j < N; j++) cin >> A[j];
        sort(A, A + N, greater<int>());
        int M; cin >> M;
        for(int j = 0; j < M; j++) {
            int x; cin >> x; pq.push(x);
        }
        int sol = 0;
        bool check = false;
        while(!pq.empty()){
            for(int j = 0; j < N && pq.size() > 0; j++){
                if(j == 0) {
                    if(A[j] < pq.top()) {
                        check = true;
                        sol = -1;
                        break;
                    }
                    pq.pop(); 
                }
                else {
                    while(!pq.empty()) {
                        if(A[j] < pq.top()) {
                            sol++;
                            pq.pop();
                        } else {
                            pq.pop();
                            break;
                        }
                    }
                }
            }
            if(check) break;
            sol++;
        }
        cout << '#' << i << ' ' << sol << '\n';
    }
    return 0;
}