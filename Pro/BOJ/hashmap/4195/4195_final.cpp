#include <iostream>
using namespace std;

#define PN 21
#define HASH_SIZE 200000
#define max(a,b) ((a>b)?(a):(b))

int p[HASH_SIZE];

struct HashMap {
    char name[HASH_SIZE][21];
    int table[HASH_SIZE][10];
    int name_idx;

    void clear() {
        name_idx = 0;
        for(register int i = 0; i < HASH_SIZE; i++)
            table[i][0] = 0;
    }

    unsigned int get_key(char *str) {
        unsigned int key = 0, p = 1;
        for(int i = 0; str[i]; i++) {
            key += str[i] * p;
            p *= PN;
        }
        return key % HASH_SIZE;
    }

    int _strcmp(char *a, char *b) {
        int i = 0;
        while(a[i]) {
            if(a[i] != b[i]) break;
            i++;
        }
        return a[i] - b[i];
    }

    int contain(char *str) {
        unsigned int key = get_key(str);
        int h_size = table[key][0];
        for(int i = 1; i <= h_size; i++) {
            int pos = table[key][i];
            if(_strcmp(str, name[pos]) == 0)
                return pos;
        }
        return -1;
    }

    int add(char *str) {
        register int i = 0;
        for(; str[i]; i++)
            name[name_idx][i] = str[i];
        name[name_idx][i] = 0;

        unsigned int key = get_key(str);
        int& h_size = table[key][0];
        table[key][++h_size] = name_idx;

        ++name_idx;
        return name_idx - 1;
    }
};

HashMap hm;

int find(int n) {
	if (p[n] < 0) return n; 
	return p[n] = find(p[n]);
}

int merge(int a, int b) {
	a = find(a);
	b = find(b);
	if(a == b) return -p[a];
    if(p[a] < p[b]) {
        p[a] += p[b];
        p[b] = a;
    }
    else {
        p[b] += p[a];
        p[a] = b;
    }
#if 0
	p[a] += p[b];
	p[b] = a;
	return -p[a];
#endif
    return max(-p[a], -p[b]); 
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int T; cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		hm.clear();
		int N; cin >> N;
		for (register int i = 0; i < N * 2; i++) p[i] = -1;
		for (register int i = 0; i < N; i++) {
			char s1[21], s2[21];
			int idx1, idx2;
			cin >> s1 >> s2;
			idx1 = hm.contain(s1); idx2 = hm.contain(s2);
			if (idx1 == -1) idx1 = hm.add(s1);
			if (idx2 == -1) idx2 = hm.add(s2);
			cout << merge(idx1, idx2) << '\n';
		}
	}
	return 0;
}
