#include <iostream>
#include <queue>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
/*
union find
dfs
recursive -> B마을 선택(조합)
base ->now == N -> B마을 연결  함수 사용, 안되는 경우 pass
*/
int N;
int Village[10];
int parent[10];
int visited[10];
int adj[10][10];
int totalCnt;//총 유권자수
int ans = 21e8;

void reset();
void input();
bool makeUnion();
void dfs(int now, int st, int cntB, int voterCnt);

int Find(int x) {
	if (x == parent[x])return x;
	return parent[x] = Find(parent[x]);
}

bool Union(int a, int b) {
	int pa = Find(a);
	int pb = Find(b);
	if (pa == pb) return false;
	parent[pb] = pa;
	return true;
}



int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	reset();
	input();
	dfs(0, 0, 0, 0);
	if (ans == 21e8) ans = -1;
	cout << ans << '\n';

	return 0;
}

void reset() {
	totalCnt = 0;
	ans = 21e8;
	memset(adj, 0, sizeof(adj));
	for (int i = 0; i < 8; i++) {
		visited[i] = 0;
	}
}

void input() {

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> Village[i];
		totalCnt += Village[i];
	}

	for (int i = 0; i < N; i++) {
		int Cnt;
		cin >> Cnt;
		for (int j = 0; j < Cnt; j++) {
			int tmp;
			cin >> tmp;
			adj[i][tmp - 1] = 1;
		}

	}


}



void dfs(int now, int st, int cntB, int voterCnt) {
	if ((now != 0 && cntB == 0) || cntB == N) return;
	if (now == N) {
		if (abs(totalCnt - 2 * voterCnt) >= ans) return;
		if (makeUnion()) {
			ans = min(ans, abs(totalCnt - 2 * voterCnt));
		}
		return;
	}
	//recursive
	for (int i = st; i < N; i++) {
		visited[i] = 1;
		dfs(now + 1, i + 1, cntB + 1, voterCnt + Village[i]);//B마을선택
		visited[i] = 0;
		dfs(now + 1, i + 1, cntB, voterCnt);//그냥가기
	}
}


bool makeUnion() {
	for (int i = 0; i < N; i++) {
		parent[i] = i;
	}
	//현재 마을 -> 이어지고(adj ==1) && 지역구 같은 마을 찾아가기
	for (int j = 0; j < N; j++) {
		queue<int>q;
		q.push(j);
		while (!q.empty()) {
			int nowVil = q.front();
			q.pop();
			for (int i = 0; i < N - 1; i++) {
				if (adj[nowVil][i] == 1 && visited[nowVil] == visited[i]) {
					if (Union(nowVil, i)) {//결합 성공시에만 넣기
						q.push(i);
					}
				}
			}
		}
	}
	int Cnt = 0;
	for (int i = 0; i < N; i++) {
		if (parent[i] == i) Cnt++;
	}
	if (Cnt == 2) return true;
	return false;
}