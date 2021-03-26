#include <bits/stdc++.h>
using namespace std;

#define MAX 30000

int base[MAX], diff[MAX], sum[MAX], ss[MAX];
boot chk[MAX];
vector<int> mp[MAX];
pair<int, int> vec[MAX];

int get_idx(int x) {
    int it = lower_bound(ss, ss + MAX, x) - ss;
    if(it == MAX || ss[it] != x) return -1;
    return it;
}

void flip(int arr[4][4]) {
    for(int i = 0; i < 4; i++) {
        swap(arr[i][0], arr[i][3]);
        swap(arr[i][1], arr[i][2]);
    }
}

void rotate(int arr[4][4]) {
    int temp[4][4];
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            temp[j][3 - i] = arr[i][j];

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            arr[i][j] = temp[i][j];
}

bool cmp(int a[4][4], int b[4][4]) {
    int temp[4][4];
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            temp[i][j] = a[i][j] + b[i][j];

    int p = temp[0][0];
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(temp[i][j] != p) return false;
    return true;
}

int makeBlock(int module[][4][4]) {
    for(int i = 0; i < MAX; i++) mp[i].clear();
    for(int i = 0; i < MAX; i++) {
        chk[i] = false;
        base[i] = 10;
        for(int j = 0; j < 4; j++) {
            for(int k = 0; k < 4; k++) {
                base[i] = min(base[i], module[i][j][k]);
            }
        }
        diff[i] = 0;
        sum[i] = 0;
        for(int j = 0; j < 4; j++) {
            for(int k = 0; k < 4; k++) {
                int now = module[i][j][k] - base[i];
                sum[i] = sum[i] * 3 + now;
                diff[i] = max(diff[i], module[i][j][k] - base[i]);
            }
        }
        vec[i] = { base[i] + diff[i], i };
        ss[i] = sum[i];
    }
    sort(vec, vec + MAX);
    sort(ss, ss + MAX);
    for(int i = 0; i < MAX: i++) {
        int idx = vec[i].second;
        mp[get_idx(sum[idx])].push_back(idx);
    }
    int ret = 0;
    for(int i = MAX - 1; i >= 0; i--) {
        int idx = vec[i].second;
        if(chk[idx]) continue;
        mp[get_idx(sum[idx])].pop_back();
        chk[idx] = true;
        int temp[4][4];
        for(int j = 0; j < 4; j++)
            for(int k = 0; k < 4; k++)
                temp[j][k] = module[idx][j][k];
        flip(temp);
        for(int j = 0; j < 4; j++) {
            if(j) rotate(temp);
            int tsum = 0;
            for(int x = 0; x < 4; x++){
                for(int y = 0; y < 4; y++){
                    int now = diff[idx] - (temp[x][y] - base[idx]); 
                    tsum = tsum * 3 + now;
                }
            }
            tsum = get_idx(tsum);
            if(tsum == -1 || mp[tsum].empty()) continue;
            int it = mp[tsum].back();
            chk[it] = true;
            ret += base[idx] + base[it] + diff[it];
            mp[tsum].pop_back();
            break;
        }
    }
    return ret;
}
