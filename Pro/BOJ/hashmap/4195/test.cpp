#include <iostream>
using namespace std;

/*
	그래프 문제.
	우선 그래프를 만들기 위해서는 이름-번호를 대응시키고, 이름을 이용해서 번호를 구할 수 있어야 한다.
	이를 위해서 이름 배열과 해시 테이블을 이용한다.

	그래프를 만들수 있게 됬다면, 친구 네트워크의 노드수를 구해야한다.
	굳이 dfs가 필요한가? union-find tree를 이용하면 되는 것 같은데.
*/

//우선 해시테이블을 구현하자. (검색, 추가만 구현해도 됨!)
const int PN = 23;
const int HASH_SIZE = 200000;
struct HashMap {
	char name[200000][21]; //최대 이름 수를 100000이라고 생각했었음...
	int table[HASH_SIZE][10];
	int name_size;

	void clear() {
		name_size = 0;
		for (register int i = 0; i < HASH_SIZE; i++)
			table[i][0] = 0;
	}

	unsigned int get_key(char _name[]) {
		unsigned int key = 0, p = 1;
		for (int i = 0; _name[i] != 0; i++) {
			key += _name[i] * p;
			p *= PN;
		}
		return key % HASH_SIZE;
	}

	int my_strcmp(char a[], char b[]) {
		int i = 0;
		while (a[i]) {
			if (a[i] != b[i]) break;
			++i;
		}
		return a[i] - b[i];
	}

	int contain(char _name[]) { //만약 존재한다면 idx를 리턴.
		unsigned int key = get_key(_name);
		int h_size = table[key][0];
		for (register int i = 1; i <= h_size; i++) { //이부분 구현 실수함 <
			int n_pos = table[key][i];
			if (my_strcmp(_name, name[n_pos]) == 0)
				return n_pos;
		}
		return -1;
	}

	int add(char _name[]) {
		register int len = 0;
		for (; _name[len] != 0; len++)
			name[name_size][len] = _name[len];
		name[name_size][len] = 0;

		unsigned int key = get_key(_name);
		int& h_size = table[key][0];
		table[key][++h_size] = name_size;

		++name_size;
		return name_size - 1;
	}
};
HashMap hm; //해시테이블 선언

//유니온 파인드 트리 구현
int p[200000]; //최대 20만개의 노드, p[n] = n의 부모 노드
int find(int n) {
	if (p[n] < 0) return n; 
	p[n] = find(p[n]); 
	return p[n];
}

int merge(int a, int b) {
	a = find(a);
	b = find(b);
	if (a == b) return -p[a];
    cout << p[a] << ' ' << p[b] << ' ' << a << endl;
	p[a] += p[b]; //루트의 절대값은 집합의 크기가 되도록 한다.
	p[b] = a;
	return -p[a];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int T; cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		int N; cin >> N;
		hm.clear();
		for (register int i = 0; i < 200000; i++) p[i] = -1; //이부분 실수함.

		for (int i = 0; i < N; i++) {
			char name1[21], name2[21];
			int idx1, idx2;
			cin >> name1 >> name2;
			//해시 테이블을 이용해서 이름과 대응하는 인덱스를 받아온다.
			idx1 = hm.contain(name1); idx2 = hm.contain(name2);
			if (idx1 == -1) idx1 = hm.add(name1);
			if (idx2 == -1) idx2 = hm.add(name2);

            cout << idx1 << ' ' << idx2 << '\n';
			//유니온 파인드 트리로 idx1와 idx2를 연결한다.
			cout << merge(idx1, idx2) << '\n';
		}
	}
	return 0;
}
