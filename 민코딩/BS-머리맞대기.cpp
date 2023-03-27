#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
/*
PS -> ���Ѽ� ã��
condition(int mid) -> mid������ T�� ������ ���� �����Ҽ� �ִ��� check
*/
int N, T;
int arr[1000];//�Է� ���翡�� N+i��ġ�� ����
int arrMax;//�Է��� ���� ū��
int ans;

void input();
void PS();
bool condition(int);

int main() {
	input();
	PS();
	cout << ans;
	return 0;
}

void input() {
	arrMax = 0;
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N >> T;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
		arr[i + N] = arr[i];//�迭 �ٿ��ֱ�
		arrMax = max(arr[i], arrMax);//�Է��� �ִ� ã��
	}
}

void PS() {
	int st = arrMax;
	int ed = arrMax * (1 + N / T);
	ans = 0;
	while (st <= ed) {
		int mid = (st + ed) / 2;
		if (condition(mid)) {// �����ϸ�
			ans = mid;
			ed = mid - 1;
		}
		else {
			st = mid + 1;
		}
	}
}

bool condition(int HeadSumMax) {

	for (int i = 0; i < 1 + N / T; i++) {
		int TeamCnt = 1;//������ ��
		int Sum = 0;
		for (int j = i; j < N + i; j++) {
			Sum += arr[j];
			if (Sum > HeadSumMax) {//Sum�� �� ũ�ٸ�, ������(j-1) ���� ������
				TeamCnt++;
				Sum = arr[j];//������� ���ο� �� ����
			}
			if (TeamCnt > T) break;
		}
		if (TeamCnt <= T) return true;//Team�� �� �����Ŵ� OK(������ ��)
	}
	return false;
}