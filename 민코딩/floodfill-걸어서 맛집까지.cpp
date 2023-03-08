#include <iostream>
#include <queue>
using namespace std;
struct Node {
	int y, x;
};
queue<Node>nextq;
int N, M;
int MAP[200][200];
int tlqkf = 0;
int sy, sx;
int result;
int visited[200][200];
//dir
int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

void input() {
	int flag = 0;//시작좌표 저장용
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> MAP[y][x];
			if (flag == 1)continue;
			if (MAP[y][x] != 0) {
				tlqkf = MAP[y][x];//
				sy = y, sx = x;
				flag = 1;
			}
		}
	}
}

void bfs() {
	//queue
	queue<Node>q;
	q.push({ sy,sx });
	//visited[]
	visited[sy][sx] = 1;


	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			if (ny >= N || ny < 0 || nx >= M || nx < 0) continue;
			if (visited[ny][nx] != 0) continue;
		
			if (MAP[ny][nx] == 0) {
				visited[ny][nx] = 1;
				nextq.push({ ny,nx });
			}
			else if(MAP[ny][nx]== tlqkf) {
				visited[ny][nx] = tlqkf;
				q.push({ ny,nx });
			}
			
		}
	}
}

void bfs2() {

	while (!nextq.empty()) {
		Node now = nextq.front();
		nextq.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			if (ny >= N || nx >= M || ny < 0 || nx < 0) continue;
			if (visited[ny][nx] != 0) continue;
			if (MAP[ny][nx] != 0) {//새로운 섬을 발견했다!
				result = visited[now.y][now.x];
				return;
			}

			visited[ny][nx] = visited[now.y][now.x] +1;
			nextq.push({ ny,nx });
			
		}
	}
}

int main() {
	input();
	bfs();

	bfs2();
	cout << result;
	return 0;
}