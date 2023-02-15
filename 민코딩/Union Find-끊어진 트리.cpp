#include <iostream>
#include <vector>

using namespace std;
int parent[200001];
int sub[200001];
vector<int>ans;
struct query {
	int sel, C, D;
};
//query 저장용 벡터
vector<query>v;

int Find(int x) {
	if (parent[x] == x) return x;

	return parent[x] = Find(parent[x]);
}

void Union(int a, int b) {
	int pa = Find(a);
	int pb = Find(b);
	if (pa == pb) return;

	parent[pb] = pa;

}

int main() {
	int N, Q;//N: 트리 정점의 개수 , Q : 쿼리의 개수
	cin >> N >> Q;
	// N-1회 끊기 >> 모든 노드 끊어짐 !! >> 초기상태!
	for (int x = 1; x <= N; x++) {
		parent[x] = x;
	}

	//sub에 parent정보 저장
	sub[1] = 1;
	for (int x = 2; x <= N; x++) {
		cin >> sub[x];
		
	}
	//vector에 저장했다가  마지막꺼 확인하고 제거
	for (int x = 0; x < N - 1 + Q; x++) {
		int sel;
		cin >> sel;
		if (sel == 0) {
			int B;
			cin >> B;
			v.push_back({ sel,B, 0 });
		}
		if (sel == 1) {
			int C, D;
			cin >> C >> D;
			v.push_back({ sel,C,D });
		}
	}


	int size = v.size();
	for (int x = size - 1; x >= 0; x--) {
		query now = v[x];

		//연결
		if (now.sel == 0) {
			Union(sub[now.C], now.C);
		}
		if (now.sel == 1) {
			if (Find(now.C) == Find(now.D)) {
				ans.push_back(1);
			}
			else ans.push_back(0);
		}
	}

	int ansize = ans.size();
	for (int x = 0; x < ansize; x++) {
		if (ans[ansize-1-x]) cout << "YES" << endl;
		else cout << "NO" << endl;
	}

	return 0;
}