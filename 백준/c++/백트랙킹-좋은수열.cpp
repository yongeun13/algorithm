#include <iostream>
using namespace std;

int N;
int path[80];
bool flag =false;

bool check(int depth, int nowNum) {
	if (depth == 0) return true;

	path[depth] = nowNum;
	for (int i = 1; i <= (depth+1) / 2; i++) {// i : üũ�� ���� ����
		//���� ������ ���� üũ

		bool isPossible = false;

		for (int j = 0; j < i; j++) {
			if (path[depth - j] != path[depth - j - i]) {
				isPossible = true;
				break;
			}
		}
		if (isPossible == false) return false;
	}
	return true;
}

void func(int now) {
	if (now == N) {
		flag = true;
		return;
	}

	//recursive
	for (int i = 1; i <= 3; i++) {
		if (!check(now, i)) continue;
		path[now] = i;
		func(now + 1);
		if (flag == true) return;//�������� ���� �߰� -> �������
	}

}


int main() {
	cin >> N;
	func(0);
	for (int i = 0; i < N; i++)cout << path[i];
	return 0;
}