#include <iostream>
#include <vector>
using namespace std;
int parent[100001];
int arr[100000];
int cnt;

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
	int T;
	cin >> T;
	int N;
	cin >> N;//차량수
	for (int x = 0; x < N; x++) {
		cin >> arr[x];
	}
	
	for (int x = 0; x <= T; x++) {
		parent[x] = x;
	}


	for (int x = 0; x < N; x++)
	{
		//x번째 차량
		//버전 같은 자리 있으면 거기에 주차
		if (parent[arr[x]] == arr[x])
			Union(arr[x] - 1, arr[x]);//다음 자리에 연결
		else {//이미 주차 되어있으면 부모 찾기
			int next = Find(arr[x]);
			if (next == 0)break;//주차공간 다 찾으면 종료
			//주차
			Union(next - 1, next);

		}
		cnt++;//주차한차량 수
			
	}
	cout << cnt;

	return 0;
}