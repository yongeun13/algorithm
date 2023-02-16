#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;
struct Edge {
	int y, x, cost;

	bool operator < (Edge next) const {
		if (cost < next.cost)
			return false;
		if (cost > next.cost)
			return true;
		return false;
	}
};
int dist[100][100];
int N;
string MAP[100];
// MAP == 1 >>  cost가 1인 것으로 간주
// 다익스트라 사용!!
//cost 반환
//시작위치 0,0 끝위치 N-1, N-1
int Dijkstra() {
	priority_queue<Edge>pq;
	pq.push({ 0,0,0 });

	//dist
	for (int x = 0; x < N; x++)
		for(int y=0; y<N; y++)
			dist[x][y] = 21e8;

	dist[0][0] = 0;

	//dir
	int ydir[] = { -1, 1, 0 , 0 };
	int xdir[] = { 0,0, -1, 1 };

	//Dijkstra
	while (!pq.empty()) {
		Edge now = pq.top();
		pq.pop();

		//현재 비용이  최솟값 보다 작으면 갈 필요 없음!!
		if (now.cost > dist[now.y][now.x]) continue;
		
		//now의 최소 비용 확정된 상태
		//종료조건
		if (now.y == N - 1 && now.x == N - 1) 
			return dist[N - 1][N - 1];

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			if (ny >= N || ny < 0 || nx >= N || nx < 0) continue;
			//다음 비용 = 지금까지 경로중 최솟값 + 다음 비용
			int temp;
			if (MAP[ny][nx] == '1') temp = 0;
			else temp = 1;
			int ncost = dist[now.y][now.x] + temp;

			//원래 최솟값 보다 작은 경우에만 우선순위 큐에 넣기
			if (ncost >= dist[ny][nx]) continue;

			dist[ny][nx] = ncost;
			//큐 안에서 코스트 낮은 순으로 재배치
			pq.push({ ny,nx,ncost });

		}

	}

}

int main() {
	cin >> N;
	for (int y = 0; y < N; y++) {
		cin >> MAP[y];
	}

	int re =Dijkstra();
	cout << re;


	return 0;
}