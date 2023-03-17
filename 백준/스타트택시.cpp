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

vector<cust>Man;//승객
int MAP[22][22];//1,1부터 시작
Node Taxi;
int usedSource = 0;//소모한 연료
/*
단계별 flood fill -> 거리 별로 승객 발견할때까지 반복
-> 승객 발견시 v 에 저장 + flag=1
-> flag ==1 이면 다음 단계로 넘어가지 못함
-> while 문 종료후 sort로 태울 승객 결정
-> 목적지 도착하면 소모한 연료 2배<-기억해야됨
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
			MAP[y][x] = 1;// 벽 둘러싸기
		}
	}
}

int main() {
	reset();
	input();
	return 0;
}