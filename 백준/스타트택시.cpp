#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;
struct Node {
	int y, x, source;
};
struct cust {
	int sy, sx, dy, dx;
};
int N, M, S;

vector<cust>Man;//�°�
int MAP[22][22];//1,1���� ����
Node Taxi;
int usedSource = 0;//�Ҹ��� ����
/*
�ܰ躰 flood fill -> �Ÿ� ���� �°� �߰��Ҷ����� �ݺ�
-> �°� �߽߰� v �� ���� + flag=1
-> flag ==1 �̸� ���� �ܰ�� �Ѿ�� ����
-> while �� ������ sort�� �¿� �°� ����
-> ������ �����ϸ� �Ҹ��� ���� 2��<-����ؾߵ�
*/





void input() {
	ios_base::sync_with_stdio;
	cin.tie(0);

	cin >> N >> M >> Taxi.source;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> MAP[y][x];
		}
	}

	cin >> Taxi.y >> Taxi.x;
	Man.reserve(M);
	for (int i = 0; i < M; i++) {
		cust tmp;
		cin >> tmp.sy>>tmp.sx>>tmp.dy>>tmp.dx;
		Man.push_back(tmp);		
	}
}

void reset() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			MAP[y][x] = 1;// �� �ѷ��α�
		}
	}
}

int main() {
	reset();
	input();
	return 0;
}