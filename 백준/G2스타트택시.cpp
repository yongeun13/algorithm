#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
struct Car {
	int y, x;//�¿� �°�
};
struct cust {
	int sy, sx, dy, dx;
};
int N, M;
int G;// ���� ���ᷮ(�Է�&���)
cust Man[410];//idx: ����̸� / val: ����&���� ��ġ
int MAP[22][22];//1,1���� ����
Car Taxi;
vector<cust>v;
/*
input -> MAP�� �°���ġ ǥ��&DAT�� ���� ����

bfs
1. �°�ã��
�ܰ躰 flood fill -> �Ÿ� ���� �°� �߰��Ҷ����� �ݺ�
-> �°� �߽߰� v �� ���� + flag=1
-> flag ==1 �̸� ���� �ܰ�� �Ѿ�� ����

2. ������ ����
-> while �� ������ sort�� �¿� �°� ����
-> ������ �����ϸ� ����= �Ҹ��� ���� 2��<-����ؾߵ�

��������
1. ���� ���ڶ� ���
2. �¿� �°��� ���°��
3. ������ ������ �� ���°��
*/

bool cmp(cust left, cust right) {
	if (left.sy < right.sy) return true;
	if (left.sy > right.sy) return false;
	if (left.sx < right.sx) return true;
	if (left.sx > right.sx) return false;
	return false;
}


// ������ ������ �� ���ٸ�  false
bool bfs() {
	//1. �°� ã��
	queue<Car>q;
	q.push(Taxi);
	int visited[22][22] = { 0, };
	visited[Taxi.y][Taxi.x] = 1;
	int ydir[] = { -1,1,0,0 };
	int xdir[] = { 0,0,-1,1 };

	int flag = 0;
	int dist = 0;
	if (MAP[Taxi.y][Taxi.x] >= 2) {
		v.push_back(Man[MAP[Taxi.y][Taxi.x]]);
		flag = 1;
	}
	while (!q.empty()) {
		int cursize = q.size();
		if (flag == 1) break;//�ִܰŸ� �߰�
		dist++;

		for (int j = 0; j < cursize; j++) {
			Car now = q.front();
			q.pop();

			for (int i = 0; i < 4; i++) {
				int ny = now.y + ydir[i];
				int nx = now.x + xdir[i];
				if (MAP[ny][nx] == 1) continue;
				if (visited[ny][nx] != 0) continue;
				if (MAP[ny][nx] >= 2) {//����߰�
					flag = 1;
					v.push_back(Man[MAP[ny][nx]]);
				}
				visited[ny][nx] = visited[now.y][now.x] + 1;
				q.push({ ny,nx });
			}
		}
	}
	//�°� �߰�
	G -= dist;//���� �Ҹ�
	if (G < 0) return false; //��������#1 ������� ���
	if (flag == 0) return false;//��������#2 �¿� �°� ���°��
	sort(v.begin(), v.end(), cmp);

	//2. ������ ����
	cust Na = v[0];// �°� �¿��
	//�ʱ�ȭ
	MAP[Na.sy][Na.sx] = 0;// �°� �¿����� �ʿ��� �����
	v.clear();
	queue<Car>().swap(q);
	memset(visited, 0, sizeof(visited));

	q.push({ Na.sy, Na.sx });
	visited[Na.sy][Na.sx] = 1;

	while (!q.empty()) {
		Car now = q.front();
		q.pop();

		//������ ����
		if (now.x == Na.dx && now.y == Na.dy) {
			if (G - visited[now.y][now.x] + 1 < 0) {
				return false;//��������#1 ������� ���
			}
			else {
				G += visited[now.y][now.x] - 1;
				Taxi = { now.y, now.x };
				return true;
			}
		}

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			if (MAP[ny][nx] == 1) continue;
			if (visited[ny][nx] != 0) continue;

			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny,nx });
		}
	}
	return false;//��������#3 ������ ������ �� ���°��
}

void solv() {
	for (int i = 0; i < M; i++) {
		bool done = bfs();

		if (done == false) {
			cout << -1;
			return;
		}
	}
	cout << G;
}


void input() {
	ios_base::sync_with_stdio;
	cin.tie(0);

	cin >> N >> M >> G;
	v.reserve(M);
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			cin >> MAP[y][x];
		}
	}

	cin >> Taxi.y >> Taxi.x;

	for (int i = 0; i < M; i++) {
		cust tmp;
		cin >> tmp.sy >> tmp.sx >> tmp.dy >> tmp.dx;
		MAP[tmp.sy][tmp.sx] = i + 2;//MAP�� ����� 2�̻����� ����
		Man[i + 2] = tmp;// idx: 2 ~ M+1
	}
}

void reset() {
	for (int y = 0; y < 22; y++) {
		for (int x = 0; x < 22; x++) {
			MAP[y][x] = 1;// �� �ѷ��α�
		}
	}
}

int main() {
	reset();
	input();
	solv();
	return 0;
}