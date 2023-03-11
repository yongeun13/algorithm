#include <iostream>
#include <algorithm>
using namespace std;
int num[10];
char oper[9];
int N;
int maxResult = -21e8;

void input() {
	cin >> N;
	for (int i = 0, j = 0; i < N; i++) {
		char tmp;
		cin >> tmp;
		if (i % 2 == 0) {
			num[j] = tmp - '0';
		}
		else {
			oper[j] = tmp;
			j++;
		}
	}

}

int calNextResult(int now, int result, int type) {
	int tmp = num[now + 1];
	if (type == 2) {
		for (int i = now + 1; i < now + type; i++) {
			if (oper[i] == '+') {
				tmp += num[i + 1];
			}
			else if (oper[i] == '-') {
				tmp -= num[i + 1];
			}
			else if (oper[i] == '*') {
				tmp *= num[i + 1];
			}
		}
	}


	if (oper[now] == '+') {
		result += tmp;
	}
	else if (oper[now] == '-') {
		result -= tmp;
	}
	else if (oper[now] == '*') {
		result *= tmp;
	}

	return result;
}

void dfs(int now, int result) {
	//base
	if (now == N / 2 + 1) {
		maxResult = max(maxResult, result);
		return;
	}

	//recursive
	int tmp = -21e8;
	for (int i = 1; i <= 2; i++) {
		if (now + i > N / 2 + 1) continue;
		int nresult = calNextResult(now, result, i);
		dfs(now + i, nresult);
	}

}


int main() {
	input();
	dfs(0, num[0]);
	cout << maxResult;
	return 0;
}