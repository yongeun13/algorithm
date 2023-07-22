#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
struct Node {
	int y, x;
};
int N;
int MAP[21][21];
int ans = 2;
vector<int>path;


/*
	dfs -> ����� �غ���
	base : 5ȸ -> �ִ� ����
	recurisive -> 4���� ���� �ߺ������� Ž��

	func Move() -> ��Ͽ����̴� �Լ�,
	two pointer�� ã��

*/

int Move(int dir) {
	int ydir[] = { -1, 0, 1, 0 };
	int xdir[] = { 0, 1, 0, -1 };
	int rdir = (dir + 1) % 4;//�ð���� ȸ��

	//Ž�� ������ġ ����
	Node startCord[4] = {//�������(�ð����)
		{N - 1,0},
		{0,0},
		{0,N - 1},
		{N - 1, N - 1}
	};
	Node now = startCord[dir];

	int Merge = 0;//������ ��

	//N���� ��/�� �� ���� �ݺ�
	for (int j = 0; j < N; j++) {
		//two pointer
		int left = 0;
		int right = 0;

		while (right < N - 1) {
			right++;
			int ly = now.y + ydir[dir] * left;
			int lx = now.x + xdir[dir] * left;
			int ry = now.y + ydir[dir] * right;
			int rx = now.x + xdir[dir] * right;

			//ó��
			if (MAP[ry][rx] == 0) continue;//����� �ǳʶٱ�


			if (MAP[ry][rx] == MAP[ly][lx]) {//1.������ ������ ��� -> ��ġ��
				MAP[ly][lx] *= 2;
				MAP[ry][rx] = 0;
				if (Merge < MAP[ly][lx]) {
					Merge = MAP[ly][lx];
				}
				left++;
			}
			else {//2. �ٸ� ��� �������
				if (MAP[ly][lx] == 0) {//left�� ����� ����Ų�ٸ�
					MAP[ly][lx] = MAP[ry][rx];
					MAP[ry][rx] = 0;
				}
				else {//left�� ����� �ִٸ�
					left++;
					if (left == right) continue;
					MAP[ly + ydir[dir]][lx + xdir[dir]] = MAP[ry][rx];
					MAP[ry][rx] = 0;
				}
			}

		}

		//���� ��, �������� �̵�
		int ny = now.y + ydir[rdir];
		int nx = now.x + xdir[rdir];
		now = { ny, nx };
	}

	return Merge;
}

void solv() {
	int tmpMAP[21][21] = { 0, };
	int tmp;
	memcpy(tmpMAP, MAP, sizeof(MAP));
	for (int i = 0; i < 5; i++) {
		tmp = Move(path[i]);
		ans = max(tmp, ans);
	}
	memcpy(MAP, tmpMAP, sizeof(MAP));
}

void dfs(int now) {
	//base
	if (now == 5) {
		solv();
		return;
	}
	//recursive
	for (int i = 0; i < 4; i++) {
		path.push_back(i);
		dfs(now + 1);
		path.pop_back();
	}
}

void input() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> MAP[y][x];
			if (MAP[y][x] == 0) continue;
			ans = max(ans, MAP[y][x]);
		}
	}
}
int main() {
	input();
	dfs(0);
	cout << ans;
	return 0;
}