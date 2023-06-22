#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
using ll = long long;
using vll = vector<ll>;
int N, M, K;
vll arr;
vll tree;


/*
segment tree
arr : (data)
tree : segment tree
node range : [st, ed]

 
query == 1 -> a번째 수를  b로 바꾸기
query == 2-> a번째수 부터 b번째 수 까지 합 구하기
*/

static void input();
static ll makeTree(int, int, int);
static ll sumTree(int, int, int,int,int);
static void updateTree(int, int, int, int ,ll);

int main() {
	
	input();
	makeTree(1, 0, N - 1);
	for (int i = 0; i < M+K; i++) {
		ll query, a, b;
		cin >> query >> a >> b;
		if (query == 1) {
			updateTree(1, a - 1, 0, N - 1, b - arr[a - 1]);
			arr[a - 1] = b;
		}
		else if (query == 2) {
			cout << sumTree(1,a-1, b-1, 0,N-1) << '\n';
		}
	}

	return 0;
}

static void input() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N >> M >> K;
	arr.resize(N,0);

	int height = (int)ceil(log2(N));
	tree.resize(1<<(height+1), 0);
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
}

static ll makeTree(int node, int st, int ed) {
	if (st == ed) return tree[node] = arr[st];
	int mid = (st + ed) / 2;

	return tree[node] = makeTree(node * 2, st, mid) + makeTree(node*2 +1, mid+1, ed);
}

static ll sumTree( int node, int left, int right, int st, int ed) {
	if (left > ed || right < st) return 0;
	if (left <= st && right >= ed) return tree[node];
	int mid = (st + ed) / 2;
	return sumTree( node * 2, left, right, st, mid) + sumTree( node * 2 + 1, left, right, mid + 1, ed);
}

static void updateTree(int node, int targetIndex, int st, int ed, ll diff) {
	if (targetIndex < st || targetIndex > ed) return;
	tree[node] += diff;
	if (st == ed) return;
	int mid = (st + ed) / 2;
	updateTree(node * 2, targetIndex, st, mid, diff);
	updateTree(node * 2 + 1, targetIndex, mid + 1, ed, diff);
}
