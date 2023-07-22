#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define STACK_SIZE 10000
/*
stack init
1. 배열
2. top 변수
3. isEmpty, isFull (배열에 저장하기 때문에 배열 크기보다 작아야함!)
주의!! -> push 할때 isFull 인지 체크!!
*/
uint32_t stack[STACK_SIZE];
int back = -1;//stack의 Top의 인덱스

int isEmpty(int top) {
	return top == -1;
}

int isFull(int top) {
	if (top >= STACK_SIZE - 1) {
		printf("Error: Stack overflow\n");
		return 1;
	}
	return 0;
}


int main() {
	
	int N;
	scanf(" %d", &N);
	for (int i = 0; i < N; i++) 
	{
		char str[10];
		scanf("%s", str);
		if (strcmp(str, "push")==0) {
			
			if (!isFull(back)) {
				int x;
				scanf(" %d", &x);
				stack[++back] = x;
			}
		}
		else if (strcmp(str, "pop") == 0)
		{
			if (isEmpty(back))
			{
				printf("%d\n", -1);
			}
			else
			{
				printf("%d\n", stack[back--]);
			}
		}
		else if (strcmp(str, "size") == 0)
		{
			printf("%d\n", back + 1);
		}
		else if (strcmp(str, "empty") == 0)
		{
			printf("%d\n", isEmpty(back));
		}
		else if (strcmp(str, "top") == 0)
		{
			if (isEmpty(back))
			{
				printf("%d\n", -1);
			}
			else
			{
				printf("%d\n", stack[back]);
			}
		}
	}

	return 0;
}