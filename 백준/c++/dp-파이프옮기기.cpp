#include <iostream>
using namespace std;
int N;
int ydir[] = {0,1,1};//가로, 세로, 대각선
int xdir[] = {1,0,1};
int Map[34][34];
long long dp[33][33][3];

/*
주의할것! -> 가장자리에 수직으로 파이프 미는 경우 때문에, dp를 3차원 배열로 선언해야함
*/

void init();
long long dfs(int nowY, int nowX, int nowDir);
bool check(int y, int x, int dir, int ndir);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	init();
	cout << dfs(1, 2, 0);
	return 0;
}

void init() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> Map[i][j];
		}
	}
	//벽으로 둘러싸기
	for (int i = 0; i <= N + 1; i++) {
		Map[0][i] = 1;
		Map[N + 1][i] = 1;
		Map[i][0] = 1;
		Map[i][N + 1] = 1;
	}
	
	//dp 초기화
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			for(int k=0; k<3; k++)
				dp[i][j][k] = -1;

	dp[N][N][0] = 1;
	dp[N][N][1] = 1;
	dp[N][N][2] = 1;
}

//nowY, nowX : 현재 파이프 끝 위치 | nowDir : 파이프가 놓여있는 방향
//return : 이동방법의 합
long long dfs(int nowY, int nowX, int nowDir) {
	//base
	if (dp[nowY][nowX][nowDir] != -1) return dp[nowY][nowX][nowDir];
	
	long long temp = 0;
	for (int i = 0; i < 3; i++) {
		if (!check(nowY, nowX, nowDir, i)) continue;
		int ny = nowY + ydir[i];
		int nx = nowX + xdir[i];
		temp += dfs(ny, nx, i);
	}
	//memoization
	return dp[nowY][nowX][nowDir] = temp;
}

bool check(int y, int x, int nowDir, int nextDir) {
	int ny = y + ydir[nextDir];
	int nx = x + xdir[nextDir];
	if (Map[ny][nx] == 1) return false;

	if (nextDir != 2) {//가로 or 세로
		if (nowDir == nextDir) return true;
		else if (nowDir == 2) return true;
		else return false;
	}
	else {//대각선
		for (int i = 0; i < 3; i++) {//벽체크
			int ty = y + ydir[i];
			int tx = x + xdir[i];
			if (Map[ty][tx] == 1) return false;
		}
		
	}
	return true;
}