#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
using namespace std;
using pii = pair<int, int>;
struct Edge {//prim ��
	int to, dist;
	bool operator <(Edge next) const {
		if (dist < next.dist) return false;
		if (dist > next.dist) return true;
		return false;
	}
};

int N, M;
int MAP[10][10];
queue<pii>nq[8];//�� ��ǥ ����
int adj[8][8];
/*
1. ��ã�� -> 2�̻����� �ٲپ� �ֱ�
2.  ������ �ٸ� ����� 
	->	 ��輱X(������ �򰥸�)
	-> ������ for������ 4���� �� ���ƺ���!
	-> 3��  for�� 
			for( 2<= k <= �������� -1)
					for( 4����)
						while( )
						�� ã���� ���� �ݺ�
						�ּڰ��� ��������Ʈ�� ����!!(����� ����) ->�ٸ�����
						�Ÿ��� 1�� ���� pass
			
3. ������� ���ϸ�-> MST ã�� ������ �ٲٱ�
	pq���(prim)

*/
int island = 2;//�� �̸�



void input(); 
void findIsland();
void bfs(int , int);
void makeBridge();
int prim();


int main() {

	input();
	findIsland();
	makeBridge();
	cout << prim();
	return 0;
}


void input() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N >> M;
	for (int y = 0; y < N; y++)
		for (int x = 0; x < M; x++) 
			cin >> MAP[y][x];

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			adj[y][x] = 21e8;//�ּڰ� ���ϱ� ���� �ʱⰪ ũ�� ����
		}
	}
}

void findIsland() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (MAP[y][x] == 1) {//���� 2 �̻����� ����� �ֱ� ������, 1�ΰ�츸 ���� ��
				bfs(y, x);
			}
								
		}
	}
}

void bfs(int sy, int sx) {
	queue<pii>q;
	q.push({ sy,sx });
	nq[island].push({ sy,sx });//�ٸ� �մ� �뵵
	MAP[sy][sx] = island;//���̸����� �ٲ��ֱ�

	int ydir[] = { -1, 1, 0, 0 };
	int xdir[] = { 0, 0, -1, 1 };
	
	while (!q.empty()) {
		pii Now = q.front();
		q.pop();
		
		for (int i = 0; i < 4; i++) {
			int ny = Now.first + ydir[i];
			int nx = Now.second + xdir[i];
			if (ny >= N || nx >= M || ny < 0 || nx < 0) continue;
			if (MAP[ny][nx] != 1) continue;
			MAP[ny][nx] = island;
			q.push({ ny,nx });
			nq[island].push({ ny,nx });
		}

	}
	island++;
}

void makeBridge() {
	int ydir[] = { -1,1,0,0 };
	int xdir[] = { 0,0, -1, 1 };

	for (int k = 2; k < island-1; k++) {
		while (!nq[k].empty()) {
			pii Now = nq[k].front();
			nq[k].pop();
			
			for (int i = 0; i < 4; i++) {
				int ny = Now.first + ydir[i];
				int nx = Now.second + xdir[i];
				if (ny >= N || nx >= M || nx < 0 || ny < 0) continue;
				if (MAP[ny][nx] == k) continue;//���� ���̸� -> �ٸ�����Ұ�
				
				int dist=0;//�ٸ� ������ �Ÿ�
				while (true) {//�ٸ��� ã��
					ny += ydir[i];
					nx += xdir[i];
					dist++;
					if (ny >= N || nx >= M || nx < 0 || ny < 0) break;
					if (2 <= MAP[ny][nx] && MAP[ny][nx] <= k) break; //(k ���� ���� �ߺ�)
					if (MAP[ny][nx] >k) {//�ٸ� �� ���� ���
						if (dist == 1) break;//�Ÿ��� 1�� �ٸ��� ������ ����
						adj[k][MAP[ny][nx]] = min(adj[k][MAP[ny][nx]], dist);//�ٸ�����
						adj[MAP[ny][nx]][k] = adj[k][MAP[ny][nx]];//����⿬��
						break;
					}
					
				}
				
			}

		}
	}
}

int prim() {
	//�ƹ� ������ ����
	priority_queue<Edge>pq;//MST��
	pq.push({2, 0});

	//MST �Ͽ����� Ȯ�ο�
	int connected[8] = { 0 };

	int sum = 0;//�Ÿ��� ��
	int cnt = 0;//����� ����

	while (!pq.empty()) {
		Edge now = pq.top(); //dist�� ���� ������ ����
		pq.pop();
		if (connected[now.to] == 1) continue;
		connected[now.to] = 1;

		sum += now.dist;
		cnt++;

		for (int i = 2; i < island; i++) {
			if (i == now.to) continue;
			if (adj[now.to][i] == 21e8) continue;//�ٸ����°�� pass
			if (connected[i] == 1) continue;//�̹� ������ ��� pass
			Edge next = { i,adj[now.to][i] };
			pq.push(next);
		}
	}
	if (cnt == island - 2) return sum;
	return -1;
}
