#include <iostream>
#include <algorithm>
using namespace std;
int N, Q;//N: 광물 수 ,  Q: 연구원 수
int mineral[100001];


void PS(int S, int E) {
	int left = 0;
	int right = N-1;
	int leftIndex = 0;//
	int rightIndex = -1;//
	int flag1 = 0;
	int flag2 = 0;
	
	while (left <= right) {
		int mid = (left + right) / 2;
		//틀리면
		if (mineral[mid] < S) {
			left = mid + 1;
		}
		else {
			flag1 = 1;
			leftIndex = mid;
			right = mid - 1;// 더 낮아도 성립하는가?ㄴ
		}
	}

	left = 0;
	right = N-1;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (mineral[mid] <= E) {
			flag2 = 1;
			rightIndex = mid;
			left = mid + 1;
		}
		else right = mid - 1;
	}

	if (flag1==1&&flag2==1)
		cout << rightIndex - leftIndex + 1 << endl;
	else cout << 0 << endl;
}

int main() {
	cin >> N >> Q;
	for (int i = 0; i < N; i++) {
		cin >> mineral[i];
	}
	sort(mineral, mineral + N);

	for (int i = 0; i < Q; i++) {
		int S, E;
		cin >> S >> E;
		PS(S, E);
	}

	return 0;
}