#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <utility>
using namespace std;
using pii = pair<int, int>;
int N, M;
int MAP[8][8];
int visited[8][8];
int wallCnt;
int ans=21e8;//새로 감염된 바이러스 수

vector<pii>virus;
vector<pii>path;
void input();
void dfs(int now);
void bfs();


int main() {
	input();
	dfs(0);
	cout << N*M-wallCnt-virus.size()-ans;
	return 0;
}

void input() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> MAP[y][x];
			if (MAP[y][x] == 1) wallCnt++;
			else if (MAP[y][x] == 2) virus.push_back({ y,x });
		}
	}
	wallCnt += 3;//벽 3개 추가해야됨
}

void dfs(int now) {
	//base
	if (ans == 0) return;
	if (now == 3) {
		bfs();
		return;
	}

	//recursive
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (visited[y][x] == 1) continue;
			if (MAP[y][x] != 0) continue;
			visited[y][x] = 1;
			path.push_back({ y,x });
			dfs(now + 1);
			visited[y][x] = 0;
			path.pop_back();
		}
	}
}

void bfs() {
	for (int i = 0; i < 3; i++) {
		MAP[path[i].first][path[i].second] = 1;
	}
	
	queue<pii>q;
	int isInfected[8][8] = { 0, };
	int virusCnt = virus.size();

	for (int i = 0; i < virusCnt; i++) {
		q.push(virus[i]);
		isInfected[virus[i].first][virus[i].second] = 1;
	}

	int ydir[] = { -1,1,0,0 };
	int xdir[] = { 0,0,-1,1 };

	virusCnt = 0;//새로운 바이러스 수

	while (!q.empty()) {
		pii now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.first + ydir[i];
			int nx = now.second + xdir[i];
			if (ny >= N || nx >= M || ny < 0 || nx < 0) continue;
			if (MAP[ny][nx] !=0) continue;
			if (isInfected[ny][nx] == 1) continue;
			isInfected[ny][nx] = 1;
			virusCnt++;//바이러스 수 증가
			q.push({ ny,nx });
		}
	}
	ans = min(ans, virusCnt);

	for (int i = 0; i < 3; i++) {
		MAP[path[i].first][path[i].second] = 0;//복구
	}
}