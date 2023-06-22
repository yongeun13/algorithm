#include <iostream>
#include <queue>
using namespace std;

int N, K;
int visited[1000001];
/*
BFS -> 탐색순서 중요
처음에 *2, +1, -1 으로 했다가 틀렸음
*2, -1, +1 순서로 하니 맞음
=>why? 작은값부터 탐색해야함!!!
*/

int main() {
	cin >> N >> K;
	if (N == K) {
		cout << 0;
		return 0;
	}

	else if (K < N) {
		cout << N - K;
		return 0;
	}

	
	queue<int>q;
	q.push(N);
	visited[N] = 1;
	
	while (!q.empty()) {
		int now = q.front();
		q.pop();

		if (now == K) {
			cout << visited[now] - 1;
			break;
		}

		//2배하기
		if (now != 0 && 2 * now <= 1000000) {
			if (visited[2 * now] == 0 || visited[2 * now] > visited[now]) {
				visited[2 * now] = visited[now];
				q.push(now * 2);
			}
		}
		//-1
		if (now != 0 && visited[now - 1] == 0) {
			visited[now - 1] = visited[now] + 1;
			q.push(now - 1);
		}
		//+1
		if (now != 1000000 && visited[now + 1] == 0) {
			visited[now + 1] = visited[now] + 1;
			q.push(now + 1);
		}

	}

	return 0;
}