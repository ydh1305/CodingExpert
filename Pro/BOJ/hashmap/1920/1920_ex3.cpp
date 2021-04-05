#include <iostream>
using namespace std;

#define HASH_SIZE 100000
#define PN 23

struct HashMap {
    int num[HASH_SIZE];
    int hash_table[HASH_SIZE][10];
    int num_idx;

    void clear() {
        num_idx = 0;
        for(int i = 0; i < HASH_SIZE; i++)
            hash_table[i][0] = 0;
    }
    unsigned int get_key(int data) {
        unsigned int key = 0, p = PN;
        key = data * p;
        return key % HASH_SIZE;
    }
    int contain(int data) {
        unsigned int key = get_key(data);
        int h_size = hash_table[key][0];
        for(int i = 1; i <= h_size; i++) {
            int pos = hash_table[key][i];
            if(data == num[pos])
                return pos;
        }
        return -1;
    }
    int insert(int data) {
        num[num_idx] = data;
        unsigned int key = get_key(data);
        int& h_size = hash_table[key][0];
        hash_table[key][++h_size] = num_idx;
        num_idx++;
        return num_idx - 1;
    }
};
HashMap hm;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int N; cin >> N;
    for(int i = 0; i < N; i++) {
        int X; cin >> X;
        hm.insert(X);
    }
    int M; cin >> M;
    for(int i = 0; i < M; i++) {
        int X; cin >> X;
        int ret = hm.contain(X);
        if(ret == -1) cout << '0' << '\n';
        else cout << '1' << '\n';
    }

    return 0;
}
