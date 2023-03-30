#include <iostream>
#include <vector>
using namespace std;
struct Fire {
	int r, c, m, s, d;
};
int N, M, K;
vector<Fire>ball;// idx : ���̾ �̸�, value : ���̾ ����
vector<Fire>temp;
vector<int>MAP[50][50];//���̾�� �̸��� �����Ѵ�

/*
sol() => ��� ���̾ �̵��� K�� �ݺ��Ѵ�
		=> K�� �ݺ����� �ʴ���, ���� ���̾�� ���� 1�� �����̸� �����Ų��

Move() => ���̾�� ������ ���� �̵���Ų��.
				��ֹ��� ���⶧���� bfs �� �ʿ� ����
				Map �� ��ǥ�� �����Ѵ�

				 nr = (N*1000 + Now.r + ydir[Now.d] * Now.s) % N
				 ����!! -> �ӵ� ~ 1000 && ydir[] == -1 �ΰ��, ���� index�� ���� �� �� ����
				 N*1000 ���ؼ� �������ֱ�!

Process() => MAP�� 2���̻��� ���̾ �� ������ ó���Ѵ�

massSum() => K�� �ݺ���, ���� fireball�� ���� ����  return�Ѵ�

*/

void input();
void sol();
void Move();
void Process();
int massSum();


int main() {
	input();
	sol();
	cout << massSum();
	return 0;
}

void input() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N >> M >> K;
	ball.reserve(N * N);
	for (int i = 0; i < M; i++) {
		int r, c, m, s, d;
		cin >> r >> c >> m >> s >> d;
		ball.push_back({ r - 1,c - 1,m,s,d });
	}
}

void sol() {
	while (K--) {
		if (ball.size() <= 1) break;
		Move();
		Process();
	}
}

void Move() {
	int ydir[] = { -1, -1, 0, 1, 1, 1,0, -1 };
	int xdir[] = { 0 , 1, 1, 1, 0, -1,-1,-1 };
	int size = ball.size();
	for (int i = 0; i < size; i++) {
		Fire Now = ball[i];
		int nr = (N * 1000 + Now.r + ydir[Now.d] * Now.s) % N;//Now.s�� ū���̸� ���� ���� �� ����
		int nc = (N * 1000 + Now.c + xdir[Now.d] * Now.s) % N;
		ball[i].r = nr;//������ġ�� �̵�
		ball[i].c = nc;
		MAP[nr][nc].push_back(i);//MAP�� �̸� ����
	}
}


void Process() {
	vector<Fire>().swap(temp);//���ο� fireball  temp�� ����
	temp.reserve(N * N);//4ms ����
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {

			int size = MAP[y][x].size();
			if (size > 1) {//2�� �̻� �����
				int mass = 0;
				int speed = 0;
				int flagD = 0;//����üũ ��
				int tmpDir = ball[MAP[y][x][0]].d % 2;
				for (int i = 0; i < size; i++) {
					mass += ball[MAP[y][x][i]].m;
					speed += ball[MAP[y][x][i]].s;
					if (tmpDir != ball[MAP[y][x][i]].d % 2) {//���� Ȧ¦ �ٸ���
						flagD = 1;
					}
				}
				//����, �ӷ� ���ϱ�
				mass /= 5;
				speed /= size;

				//#3 ��ġ��
				if (mass == 0) continue;//���� 0�̸� ����
				if (flagD == 0) {//��� ���� Ȧ¦ ������
					for (int j = 0; j < 8; j += 2) {
						temp.push_back({ y,x,mass,speed,j });
					}
				}
				else {
					for (int j = 1; j < 8; j += 2) {
						temp.push_back({ y,x,mass,speed,j });
					}
				}
			}
			else if (size == 1) {//1�� �����
				temp.push_back(ball[MAP[y][x][0]]);
			}
		}
	}
	temp.swap(ball);//ball�� temp ���� 
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			MAP[y][x].clear();
		}
	}
}

int massSum() {
	int ans = 0;
	int size = ball.size();
	for (int i = 0; i < size; i++) {
		ans += ball[i].m;
	}
	return ans;
}
