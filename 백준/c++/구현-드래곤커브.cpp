#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
struct Node {
	int x, y, d, g;
};
struct Cord {
	int x, y;
};
int N;
vector<Node>dragonCurve;
int Map[101][101];
int ydir[] = { 0,-1,0,1 };//우 상 좌 하
int xdir[] = { 1,0,-1,0 };
vector<Cord>temp;

void init();
void makeDragonCurve(Node, int);
Cord rotate(int, int, int, int);

int main() {
	init();
	for (int i = 0; i < dragonCurve.size(); i++) {
		makeDragonCurve(dragonCurve[i], 0);
	}
	int ans = 0;
	for (int x = 0; x < 100; x++) {
		for (int y = 0; y < 100; y++) {
			if (Map[x][y] == 0) continue;
			//x, y -> 시작점
			bool flag = true;
			for (int i = 0; i <= 1; i++) {
				for (int j = 0; j <= 1; j++) {
					if (Map[x + i][y + j] == 0) {
						flag = false;
						break;
					}
				}
			}
			if (flag == true) ans++;
		}
	}
	cout << ans;
	return 0;
}

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++) {
		int x, y, d, g;
		cin >> x >> y >> d >> g;
		dragonCurve.push_back({ x,y,d,g });
	}
}


//재귀 이용 -> 드래곤 커브 구현
void makeDragonCurve(Node now, int cnt) {
	if (cnt == 0) temp.clear();//시작시 초기화
	if (now.g == 0) {
		int ny = now.y + ydir[now.d];
		int nx = now.x + xdir[now.d];
		Map[nx][ny]++;
		Map[now.x][now.y]++;
		temp.push_back({ now.x, now.y });
		temp.push_back({ nx,ny });
		return;
	}
	Node next = { now.x, now.y, now.d, now.g - 1 };
	makeDragonCurve(next, cnt + 1);
	//후위 처리(temp 의 가장 마지막 좌표가 기준점)
	int size = temp.size();
	for (int i = size - 2; i >= 0; i--) {
		Cord rot = rotate(temp[i].x, temp[i].y, temp[size - 1].x, temp[size - 1].y);
		temp.push_back(rot);
		Map[rot.x][rot.y]++;
	}

}

// 회전할 좌표, 기준점 좌표
//시계방향 90도 회전한 좌표 반환
Cord rotate(int nowX, int nowY, int baseX, int baseY) {
	int nx, ny;
	int vx = nowX - baseX;
	int vy = nowY - baseY;
	nx = baseX - vy;// 회전변화
	ny = baseY + vx;
	return { nx,ny };
}