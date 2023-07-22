#include <iostream>
#include <algorithm>
using namespace std;

int N, K;
int W[100];
int V[100];
int dp[100][100000];//�� : ����, �� :  ����
/*
dp �ʱⰪ�� �ݵ�� 0���� �ʱ�ȭ �ؾ���
����ǥ�� 0�� ���� ù ��° �������� ������ �� �����Ƿ�,
�ش� ���Կ� ���� �ִ� ��ġ�� �׻� 0
���������� ����ǥ�� 0�� ���� �������� �������� �ʴ� ����̹Ƿ� �ִ� ��ġ�� 0

dp �ʱ�ȭ ���1. 0���� �ʱ�ȭ => �̷� ����
                            2. �ſ�ū ���� (�Ǵ� ���)�� �ʱ�ȭ

*/
void input();
int findMaxV(int, int);

int main() {
    input();
    // findMaxV(0, K);
    //cout << dp[0][K];
    cout << findMaxV(0, K);//return �ϸ鼭 dp[0][K]�� ���� ���ŵ�
    return 0;
}

void input() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        int w, v;
        cin >> w >> v;
        W[i] = w;
        V[i] = v;
    }
}

//now : ���� ����, weight : ���� ����
int findMaxV(int now, int weight) {
    //base
    if (weight < 0) return -21e8;             // weight�� ������ ��� => ����(�ִ� �ɼ� ���� �����)
    if (weight == 0) return 0;                  //���Ը� ��� ä�� ���=>  ����1
    if (now == N) return 0;                     //��� ������ ����� ���=> ����2
    if (dp[now][weight] != 0) return dp[now][weight];//�ߺ�����

    //recursive
    int temp1 = findMaxV(now + 1, weight);                                  //���� ���� ���� ���ϴ� ���
    int temp2 = findMaxV(now + 1, weight - W[now]) + V[now];//���� ����  �賶�� ��°��
    return dp[now][weight] = max(temp1, temp2);//���� �ִ� dp�� ����
    // dp[now][weight] = max(temp1, temp2);
   //return dp[now][weight]; //�̰� �� ������ ���
}