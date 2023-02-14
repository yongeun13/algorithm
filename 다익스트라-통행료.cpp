#include <iostream>
#include <vector>
#include <queue>
using namespace std;
//매년 cost 인상
int N, M, K;
struct Edge {
	int to, cost;
	bool operator < (Edge next) const {
		if (cost < next.cost)
			return false;
		if (cost > next.cost)
			return true;
		return false;
	}
};


vector<Edge>v[1001]; // idx : 도시 node
int charge[30001];

int Dijkstra(int st, int end) {
	//queue;
	priority_queue<Edge>pq;
	pq.push({ st, 0 });

	//dist
	int dist[1001] = { 0, };
	int Max = 21e8;
	for (int x = 0; x <= N; x++) {
		dist[x] = Max;
	}
	dist[st] = 0;

	//dijkstra
	while (!pq.empty()) {
		Edge now = pq.top();
		pq.pop();

		if (dist[now.to] < now.cost)
			continue;
		//종료 노드에서 가는 건 의미없음!!
		if (now.to == end) {
			return dist[end];
		}

		int size = v[now.to].size();
		for (int i = 0; i < size; i++) {
			Edge next = v[now.to][i];
			//ncost

			int ncost = dist[now.to] + next.cost;

			if (ncost >= dist[next.to])
				continue;

			dist[next.to] = ncost;

			pq.push({ next.to, ncost });

		}

	}

	


}

void plusCharge(int idx)
{
	for (int x = 1; x <= N; x++) {
		for (int y = 0; y < v[x].size(); y++) {
			v[x][y].cost += charge[idx];
		}
	}
}

int main() {
	
	cin >> N >> M >> K;
	int st, end;
	cin >> st >> end;

	for (int x = 0; x < M; x++) {
		int from, to, cost;
		cin >> from >> to >> cost;
		v[from].push_back({ to,cost });
		v[to].push_back({ from,cost });
	}
	for (int y = 1; y <= K; y++)
	{
		cin >> charge[y];
	}

	
	for (int x = 0; x <= K; x++) {
		
		plusCharge(x);
		int re = Dijkstra(st, end);
		cout << re << endl;


	}




	return 0;


	}