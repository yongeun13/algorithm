#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
struct Schedule {
	int days, cost;
};
int N;
int dp[200];
vector<Schedule>v[101];

void input() {
	cin >> N;
	for (int x = 1; x <= N; x++) {
		int days, cost;
		cin >> days >> cost;
		v[x].push_back({ days, cost });
	}
	for (int x = 0; x < 200; x++) {
		dp[x] = -21e8;
	}
}
int func(int now) {
	//base
	if (now > N)
		return 0;
	if (dp[now] != -21e8) {
		return dp[now];
	}
	//recursive
	int tmp1 = func(now + 1);
	int tmp2 = func(now + v[now][0].days) + v[now][0].cost;

	return dp[now] = max(tmp1, tmp2);
}

int main() {
	input();
	cout <<func(1);
	return 0;
}