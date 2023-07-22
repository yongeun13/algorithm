#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_N 101
using namespace std;
struct Node {
	int to, cost;
};
int N, M;
int dp[MAX_N][MAX_N];

vector<Node>al[MAX_N];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M;

	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			dp[y][x] = 10e8;//초기값 == 더했을 때 오버플로우 안나는값
		}
	}
	for (int i = 1; i <= N; i++) dp[i][i] = 0;//자기자신으로 가는건 0으로 초기화

	for (int i = 0; i < M; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		dp[a][b] = min(dp[a][b], c);
	}

	for (int k = 1; k <= N; k++) {//경유지가 기준!
		for (int i = 1; i <=N; i++) {
			for (int j = 1; j <= N; j++) {
				//경유해서 가는게 바로가는것 보다 빠르면, 갱신
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
			}

		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (dp[i][j] == 10e8) cout << "0 ";//INF 인경우
			else {
				cout << dp[i][j] << " ";
			}
		}
		cout << endl;
	}

	return 0;
}