#include <iostream>
using namespace std;

int main() {
	int N, M, P;
	cin >> N >> M >> P;
	int arr[100000] = { 0, };
	for (int x = 0; x < N; x++) {
		cin >> arr[x];
	}

	if (N == M) {
		int temp = 0;
		for (int x = 0; x < N; x++) {
			temp += arr[x];
		}
		if (temp < P) cout << 1;
		else cout << 0;
		return 0;

	}

	//pointer setting
	int left = 0;
	int right = M - 1;

	// �ʱ� ���� setting
	int cnt = 0;
	int sum = 0;

	for (int x = left; x < right; x++) {
		sum += arr[x];
	}

	//sliding window
	while (left < N) {
		// �ϼ�
		sum += arr[right];

		//ó����
		if (sum < P) {
			cnt++;
		}

		//�ٽ� �ڿ��� ��
		sum -= arr[left];

		//������ ��ġ �Ű�
		left++;
		right = (N + right + 1) % N;
	}

	cout << cnt;

	return 0;
}