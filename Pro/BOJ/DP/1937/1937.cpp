#include <iostream>
using namespace std;

int N;
int map[500][500];
int dp[500][500];
int hh[4] = { -1, 1, 0, 0 };
int ww[4] = { 0, 0, -1, 1 };

int DFS(int h, int w) {
	int& ret = dp[h][w];
	if(ret) return ret;
	ret = 1;
	for(int i = 0; i < 4; ++i) {
		int H = h + hh[i];
		int W = w + ww[i];
		if(H < 0 || W < 0 || H > N - 1 || W > N - 1) continue;
		if(map[h][w] < map[H][W])
			ret = max(ret, DFS(H, W) + 1);
	}
	return ret;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> N;
	for(int h = 0; h < N; ++h)
		for(int w = 0; w < N; ++w)
			cin >> map[h][w];
	int sol = 0;
	for(int h = 0; h < N; ++h)
		for(int w = 0; w < N; ++w)
			sol = max(sol, DFS(h, w));
	cout << sol << '\n';
	return 0;
}
