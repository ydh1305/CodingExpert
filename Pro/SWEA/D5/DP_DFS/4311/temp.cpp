#include <iostream>
using namespace std;
 
int N, O, M, W;
bool bN[10], bO[4];
int iN[1000], iO[4], len[1000];
int res, zero, idx;
int direct() {
 
    int d = W % 10;
    int count = 0;
    if (bN[d]) ++count;
    else return 0;
     
    if (W > 9) {
        d = (W % 100) / 10;
        if (bN[d]) ++count;
        else return 0;
    }
 
    if (W > 99) {
        d = W / 100;
        if (bN[d]) ++count;
        else return 0;
    }
    res = count;
    return 1;
}
 
inline int oper(const int& o, const int& a, const int& b) {
    switch (o) {
    case 0: return a + b;
    case 1: return a - b;
    case 2: return a * b;
    case 3: return a / b;
    }
}
 
void loop(int m, int w) {
 
    if (m + 1 > M || m + 1 >= res) return;
     
    if (w == W) {
        res = m + 1;
        return;
    }
 
    for (register int i = zero; i < idx; ++i) {
        int nm = m + 1 + len[iN[i]];
        if (nm + 1 > M || nm + 1 > res) continue;
 
        for (register int j = 0; j < O; ++j) {
            int nw = oper(iO[j], w, iN[i]);
            if (nw != W && (nm + 3 > M || nm + 3 >= res)) continue;
            if (nw <= 0 || nw > 999) continue;
            if (len[nw] > nm) {
                len[nw] = nm;
                loop(nm, nw);
            }
        }
    }
}
 
void sol() {
 
    if (direct())
        return;
 
    if (W == 0) {
        if (bO[1]) {
            res = 4;
            return;
        }
        if (bO[3]) {
            res = 5;
            return;
        }
    }
 
    register int z;
    for (z = 0; z < N; ++z) {
        if (iN[z] == 0) {
            swap(iN[0], iN[z]);
            break;
        }
    }
    zero = (z == N) ? 0 : 1;
    idx = N;
    for (register int i = zero; i < N; ++i) {
        for (register int j = 0; j < N; ++j) {
            iN[idx] = iN[i] * 10 + iN[j];
            len[iN[idx]] = 2;
            ++idx;
        }
    }
 
    for (register int i = zero; i < N; ++i) {
        for (register int j = 0; j < N; ++j) {
            for (register int k = 0; k < N; ++k) {
                iN[idx] = iN[i] * 100 + iN[j] * 10 + iN[k];
                len[iN[idx]] = 3;
                ++idx;
            }
        }
    }
 
    for (register int i = 0; i < idx; ++i) {
        loop(len[iN[i]], iN[i]);
    }
     
    if (res == 999) res = -1;
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);
 
    int T; cin >> T;
    for (register int t = 1; t <= T; ++t) {
 
        for (register int i = 0; i < 1000; i += 2) {
            len[i] = len[i + 1] = 999;
        }
        bO[0] = bO[1] = bO[2] = bO[3] = 0;
        for (register int i = 0; i < 10; i += 2) {
            bN[i] = bN[i + 1] = 0;
        }
     
        res = 999;
        cin >> N >> O >> M;
 
        for (register int i = 0; i < N; ++i) {
            cin >> iN[i];
            bN[iN[i]] = 1;
            len[iN[i]] = 1;
        }
 
        for (register int i = 0; i < O; ++i) {
            cin >> iO[i];
            --iO[i];
            bO[iO[i]] = 1;
        }
        cin >> W;
        sol();
        cout << '#' << t << ' ' << res << '\n';
    }
 
    return 0;
}