#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
주의할점
1. Null pointer Access Error -> 처음에 Queue 생성시, 포인터가 아닌 Queue q; 와 같이 구조체 변수로 생성한다!(아니면 Null 주소에 접근하게됨)
2. 구조체 포인터에서 맴버변수 접근 queue->front
3. 구조체에서 맴버변수 접근 q.front
=>pointer로 받을지, 변수로 받을지 잘 생각해서 적절한 연산자 사용하기!!
4. malloc 사용법 숙지

*/
typedef struct Node
{
	int data;
	struct Node* next;
}Node;

typedef struct Queue
{
	Node* front;
	Node* rear;
	int count;// 내부의 node 개수
}Queue;

void initQueue(Queue* queue)
{
	queue->front = queue->rear = NULL; //queue 초기화
	queue->count = 0;
}

int isEmpty(Queue* queue)
{
	return queue->count == 0;
}

void enqueue(Queue* queue, int data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));// newNode 생성
	newNode->data = data;
	newNode->next = NULL;

	if (isEmpty(queue))
	{
		queue->front = newNode;
	}
	else
	{
		queue->rear->next = newNode;
	}
	queue->rear = newNode;
	queue->count++;
}

int dequeue(Queue* queue)
{
	if (isEmpty(queue)) 
	{
		//printf("Error: queue is empty!!\n");
		return -1;
	}
	
	int data;
	Node* ptr;
	ptr = queue->front;
	data = ptr->data;
	queue->front = ptr->next;
	free(ptr);
	queue->count--;

	return data;
}



int main() {
	
	int N;
	Queue q;
	initQueue(&q);

	scanf(" %d", &N);
	for (int i = 0; i < N; i++) {
		char str[10];
		scanf("%s", str);
		if (strcmp(str, "push") == 0)
		{
			int x;
			scanf(" %d", &x);
			enqueue(&q, x);
		}
		else if (strcmp(str, "pop") == 0)
		{
			int front = dequeue(&q);
			printf("%d\n", front);
		}
		else if (strcmp(str, "size") == 0) 
		{
			printf("%d\n", q.count);
		}
		else if (strcmp(str, "empty") == 0)
		{
			printf("%d\n", isEmpty(&q));
		}
		else if (strcmp(str, "front")== 0) 
		{
			if (isEmpty(&q)) 
			{
				printf("%d\n", -1);
			}
			else {
				printf("%d\n", q.front->data);
			}
			
		}
		else if (strcmp(str, "back") == 0) {
			if (isEmpty(&q)) 
			{
				printf("%d\n", -1);
			}
			else
			{
				printf("%d\n", q.rear->data);
			}
		}
		else
		{
			printf("Error::invalid command\n");
		}
	}
	return 0;
}