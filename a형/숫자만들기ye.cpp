#include <iostream>
#include <algorithm>
using namespace std;
int N;
int Result;
int MAP[12];//�Է¹��� ��
int minS, maxS;
int oper[4];

void DFS(int now) {
    //����

    if (now == N) {
        //�ִ�, �ּҰ� ����
        // 
        //minS : ���� ��� �� ��  �ּڰ�, Result: ���� ������
        minS = min(minS, Result);
        maxS = max(maxS, Result);

        return;
    }


    for (int i = 0; i < 4; i++) {
        //����ġ��
        if (oper[i] == 0) continue;//������ �� ����� ��� skip

        int temp = Result; // ������
        //ó��: Result�� ������ ����
        if (i == 0) {
            Result = Result + MAP[now];
        }
        else if (i == 1) {
            Result -= MAP[now];
        }
        else if (i == 2) {
            Result *= MAP[now];
        }
        else {
            Result = Result / MAP[now];
        }

        oper[i]--;//���Ƚ������
        DFS(now + 1);//�⺻����
        //����
        oper[i]++;

        Result = temp;

    }

}

int main() {

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        //reset
        minS = 21e8;
        maxS = -21e8;
        Result = 0;

        //input
        cin >> N;
        for (int x = 0; x < 4; x++) {
            cin >> oper[x];
        }
        for (int x = 0; x < N; x++) {
            cin >> MAP[x];
        }

        //solve
        Result = MAP[0];// �Է¹��� ��ó�� ���� result�� �ʱ�ȭ
        DFS(1);

        //output
        //DFS ���� ���� maxS �� minS ���
        cout << "#" << tc << " " << maxS - minS << endl;

    }


    return 0;
}