#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct cord {
	int y, x;
};

int N,M;
int chicDistOfCity =21e8;
vector<cord>Home;
vector<cord>Chic;
vector<cord>path;
//dfs ->���� -> ��ü ġŲ�� �߿� M���� ġŲ�� ����
// ��� ���� �� ġŲ �Ÿ� �ּڰ� ���ϱ�

void input() {
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			int tmp;
			cin >>tmp;
			if (tmp == 1) {
				Home.push_back({ y,x });
			}
			if (tmp == 2) {
				Chic.push_back({y,x});
			}
		}
	}
}
//return : �� ������ �Ÿ�
int getDist(int y1, int x1, int y2, int x2) {
	int ry = y1 - y2;
	int rx = x1 - x2;
	if (ry < 0) ry = -ry;
	if (rx < 0) rx = -rx;
	return ry + rx;
}
//2��for������ ����� Ž��
void solv() {
	int ret = 0;
	for (int i = 0; i < Home.size(); i++) {
		int mintmp = 21e8;
		cord home = Home[i];
		for (int j = 0; j < M; j++) {
			mintmp = min(mintmp, getDist(home.y, home.x, path[j].y, path[j].x));
		}
		ret += mintmp;
	}
	chicDistOfCity = min(ret, chicDistOfCity);
}

void dfs(int now , int st) {
	//base
	if (now == M) {
		solv();
		return;
	}

	int size = Chic.size();
	for (int i = st; i < size; i++) {
		path.push_back(Chic[i]);
		dfs(now + 1, i + 1);//����
		path.pop_back();
	}
}

int main() {
	
	input();
	dfs(0, 0);
	cout << chicDistOfCity;
	return 0;
}