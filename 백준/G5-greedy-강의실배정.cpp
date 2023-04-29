#include <iostream>
#include <algorithm>
#include <queue>
#define MAX_N 200000
using namespace std;

struct Node {
    int st, ed;
    bool operator <(const Node& right) const {
        return ed > right.ed; // 끝나는 시간이 빠른 순으로 정렬
    }
};

priority_queue<int, vector<int>, greater<int>> pq;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;
    vector<Node> courses(N);//N개의 강의 생성
    for (int i = 0; i < N; i++) {
        cin >> courses[i].st >> courses[i].ed;
    }
    sort(courses.begin(), courses.end(), [](const Node& a, const Node& b) {
        return a.st < b.st; // 시작 시간이 빠른 순으로 정렬
        });

    pq.push(courses[0].ed);//
    for (int i = 1; i < N; i++) {
        if (pq.top() <= courses[i].st) { // 가장 빨리 끝나는 강의실이 이용 가능한 경우
            pq.pop();
        }
        pq.push(courses[i].ed);
    }

    cout << pq.size() << endl;

    return 0;
}