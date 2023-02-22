#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
int MAP[20][20];
int homeCnt;
int N, M;
int cost;
struct Node {
	int y, x;
};
void input() {
	//reset,
	homeCnt = 0;

	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> MAP[y][x];
		}
	}
}
//�ܰ躰 flood fill
// day���� ������ ���� �� day�� �̿��� cost�� ����Ѵ�!!
//cost >=0 �϶�Cnt�� �ִ���  ����, ����� return
int BFS(int sy, int sx) {
	
	//queue
	queue<Node>q;
	q.push({ sy,sx });
	//visited
	int visited[20][20] = { 0, };
	visited[sy][sx] = 1;
	//dir
	int ydir[] = { -1,1,0,0 };
	int xdir[] = { 0,0,-1,1 };
	//variables
	int K = 0;
	int maxCnt=0;
	int Cnt = MAP[sy][sx];//���� ������ ���� ��
	while (!q.empty()) {
		K++;
		if (K > N) break;
		int nowsize = q.size();
		//cost���
		cost =  M*Cnt - (K * K + (K - 1) * (K - 1));
		//����
		if (cost >= 0)
			maxCnt = max(maxCnt, Cnt);

		for (int x = 0; x < nowsize; x++) {
			Node now = q.front();
			q.pop();

			for (int i = 0; i < 4; i++) {
				int ny = now.y + ydir[i];
				int nx = now.x + xdir[i];
				if (ny >= N || ny < 0 || nx >= N || nx < 0) continue;//MAP���
				if (visited[ny][nx] != 0) continue;//�̹� �湮
				//ó��
				if (MAP[ny][nx] == 1) {
					Cnt++;
				}
				visited[ny][nx] = visited[now.y][now.x] + 1;
				q.push({ ny,nx });

			}
		}
		
		
	}
	return maxCnt;

}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		input();

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {

				int tmp=BFS(y, x);//maxCnt�� ����
				homeCnt = max(homeCnt, tmp);
			}
		}
		cout << "#" << tc << " " << homeCnt << endl;
	}
	
	return 0;
}