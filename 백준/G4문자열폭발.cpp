#include <iostream>
#include <string>
#include <vector>
using namespace std;

string inputStr;
string targetStr;
int inputLen;
vector<char>ans;

void run();

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> inputStr >> targetStr;
	inputLen = inputStr.length();
	ans.reserve(inputLen);
	run();

	int ansLen = ans.size();
	if (ansLen != 0) {
		for (int i = 0; i < ansLen; i++) {
			cout << ans[i];
		}
	}
	else cout << "FRULA";
	return 0;
}

void run() {
	int targetLen = targetStr.length();

	char target = targetStr[targetLen-1];//target의 맨끝 문자
	
	if (targetStr != inputStr.substr(0, targetLen)) {
		for (int i = 0; i < targetLen; i++) {
			ans.push_back(inputStr[i]);
		}
	}
	for (int i = targetLen; i < inputLen; i++) {
		ans.push_back(inputStr[i]);
		if (inputStr[i] == target) {//target의 맨 끝문자가 들어온경우
			int size = ans.size();
			bool flag = false;
			int j = 0;
			while (j != targetLen) {//target인지 확인(역순으로)
				if (ans[size - 1 - j] != targetStr[targetLen - 1 - j]) {
					flag = true;
					break;
				}
				j++;
			}
			if (flag == false) {//맞으면 제거
				while (j--) ans.pop_back();
			}
		}
		
	}
}
