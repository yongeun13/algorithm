#include <iostream>
#include <algorithm>
using namespace std;

int Schedule[12];//idx : month -1 , ��: �̿��ȹ
int Charge[4]; // ���
int minCost;// �ּڰ� ���ſ�
int Sum; //������ �����

//visited �ʿ����

void DFS(int now) {
    //����
    if (now >= 12) {
        //12�� �ʰ��ϸ� �ּڰ� ����
        minCost = min(minCost, Sum);
        return;
    }

    for (int x = 0; x < 3; x++) {
        //����ġ��

        //���� �ּڰ� �̻��� skip
        if (Sum >= minCost) continue;


        //ó��
        //���� �̿��
        if (x == 0) {
            Sum += Schedule[now] * Charge[x];
            DFS(now + 1);
            Sum -= Schedule[now] * Charge[x];
        }
        //����
        if (x == 1) {
            Sum += Charge[x];
            DFS(now + 1);
            Sum -= Charge[x];
        }
        //3��
        if (x == 2) {
            Sum += Charge[x];
            DFS(now + 3);
            Sum -= Charge[x];
        }


    }


}


int main() {

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        //reset
        Sum = 0;
        //input
        for (int x = 0; x < 4; x++)
            cin >> Charge[x];

        for (int x = 0; x < 12; x++)
            cin >> Schedule[x];

        minCost = Charge[3]; //�����̿�� �������� �ʱ�ȭ

        DFS(0);

        //DFS�� ���ŵ� �ּڰ� ���
        cout << "#" << tc << " " << minCost << endl;

    }

    return 0;
}