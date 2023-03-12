#include <iostream>
#include <vector>
using namespace std;
struct Node {
	int y, x;
};
int N;
//dir: 0 ->가로,1->세로, 2-> 대각선
int ydir[] = { 0,1,1 };
int xdir[] = { 1,0,1 };
int ans;
int MAP[16][16];
vector<Node>path;

bool checkdir(int now, int next, int nowy,int nowx) {
	//대각선
	if (next == 2) {
		for (int i = 0; i < 3; i++) {
			if (MAP[nowy+ydir[i]][nowx+xdir[i]] == 1) return false;
		}
	}
	//가로
	else if (next == 0) {
		if (now== 1) return false;
		if (MAP[nowy][nowx+1] == 1)return false;
		
	}
	//세로
	else if (next == 1) {
		if (now == 0) return false;
		if (MAP[nowy + 1][nowx] == 1)return false;
	}
	return true;
}

void dfs(int y, int x, int nowdir) {
	//base
	if (y == N - 1 && x == N - 1) {
		ans++;
		return;
	}
	//recursive
	for (int i = 0; i < 3; i++) {
		int ny = y +ydir[i];
		int nx = x + xdir[i];
		if (ny >= N || nx >= N) continue;
		if (!checkdir(nowdir, i, y,x)) continue;
		dfs(ny, nx, i);
	}
}


void input() {
	cin >> N;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> MAP[y][x];
		}
	}
}

int main() {
	input();
	dfs(0,1,0);
	cout << ans;
	return 0;
}