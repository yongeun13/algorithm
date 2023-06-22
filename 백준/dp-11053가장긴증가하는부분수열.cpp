#include <iostream>
#include <algorithm>
#define MAX_N 1000
using namespace std;
int N;
int A[MAX_N];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++) cin >> A[i];

	int ans = 1;
	int dp[MAX_N] = { 0, };
	
	for (int i = 0; i < N; i++) {
		dp[i] = 1;
		for (int j = i-1; j >= 0 ; j--) {
			if (A[i] > A[j]) {
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
		ans = max(dp[i], ans);
	}
	cout << ans;
	return 0;
}