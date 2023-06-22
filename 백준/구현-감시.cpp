#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

struct Node {
	int y, x, num;//ī�޶� ����
};
int N, M;
int ans= 21e8;
int Map[8][8];
int detected[8][8];//���� ���ɿ���
vector<Node>camera; //ī�޶� ���� ����
vector<int>v[6] = {
	{},
	{0,1,2,3},//1����ī -> ������ ����
	{0,2},//2����ī -> (0, 1) || (2 ,3)  -> dir+1
	{0,1,2,3},//3����ī ->�ڱ� ������ Ž�� 
	{0,1,2,3}, // 4����ī
	{0}
};

/*
dfs->����ī�޶� ���� ���� �ִ� ��� Ž��
v[].size() ��ŭ edge ����
detecting() -> ���õǴ� ���� ǥ���ϱ�
*/


int findCnt() {
	int Cnt =0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (detected[y][x] == 0) Cnt++;
		}
	}
	return Cnt;
}
//�����ϱ�
void detecting(int sy, int sx, int dir) {
	int ydir[] = { -1, 1, 0 ,0 };
	int xdir[] = { 0,0,-1, 1 };
	int nowX = sx;
	int nowY = sy;
	while (true) {
		int ny = nowY + ydir[dir];
		int nx = nowX + xdir[dir];
		if (ny >= N || nx >= M || ny < 0 || nx < 0) break;
		if (Map[ny][nx] == 6) break;

		detected[ny][nx] = 1;
		nowX = nx;
		nowY = ny;
	}
}

//now.num == ī�޶� ����
//type Ž�� ����
void Process(Node now, int type) {
	if (now.num == 1) {
		detecting(now.y, now.x, type);
	}
	else if (now.num == 2) {
		detecting(now.y, now.x, type);
		detecting(now.y, now.x, type + 1);
	}
	else if (now.num == 3) {
		if (type == 0) {
			detecting(now.y, now.x, 0);
			detecting(now.y, now.x, 3);
		}
		else if (type == 1) {
			detecting(now.y, now.x, 1);
			detecting(now.y, now.x, 2);
		}
		else if (type == 2) {
			detecting(now.y, now.x, 2);
			detecting(now.y, now.x, 0);
		}
		else {
			detecting(now.y, now.x, 3);
			detecting(now.y, now.x, 1);
		}
	}
	else if(now.num == 4){
		for (int i = 0; i < 4; i++) {
			if (i == type)continue;
			detecting(now.y, now.x, i);
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			detecting(now.y, now.x, i);
		}
	}
}

void dfs(int now) {
	//base
	if (ans == 0) return;
	if (now == camera.size()) {
		int tmp = findCnt();
		ans = min(ans, tmp);
		return;
	}
	
	//recursive
	int tmp[8][8];//������
	memcpy(tmp, detected, sizeof(detected));
	
	int size = v[camera[now].num].size();
	for (int i = 0; i < size; i++) {
		Process(camera[now], v[camera[now].num][i]);
		dfs(now + 1);
		memcpy(detected, tmp, sizeof(detected));
	}

}


void input() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	camera.reserve(8);
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			int tmp;
			cin >>tmp;
			Map[y][x] = tmp;
			if (tmp == 0) continue;
			detected[y][x] = 1;
			if (1 <= tmp && tmp <= 5) {
				camera.push_back({ y,x ,tmp });
			}
		}
	}
}

int main() {
	input();
	dfs(0);
	cout << ans;
	return 0;
}