#include <stdio.h>
#include <stdlib.h>

#define RADIX 10	// 정렬할 자료들의 키값이 10진수이므로 RADIX를 10으로 정의
#define DIGIT 2		// 정렬할 자료들의 키값이 두 자리이므로 DIGIT을 2로 정의

// Queue Operation : 
typedef int element;

typedef struct QNode {
	element data;
	struct QNode *link;
}QNode;

typedef struct {
	QNode *front, *rear;
}LQueueType;


LQueueType* createLinkedQueue();
int isEmpty(LQueueType *LQ);
void enQueue(LQueueType *LQ, element item);
element deQueue(LQueueType *LQ);
void radixSort(element a[], int n);

int main()
{
	element list[] = { 69, 10, 30, 2, 16, 8, 31, 22 };
	int size = sizeof(list) / sizeof(list[0]);

	printf("\n <<<<<< 기수 정렬 수행 >>>>>>");
	radixSort(list, size);
	printf("\n\n");

	return 0;
}
LQueueType* createLinkedQueue() {
	LQueueType *LQ;
	LQ = (LQueueType *)malloc(sizeof(LQueueType));
	LQ->front = NULL;
	LQ->rear = NULL;
	return LQ;
}

int isEmpty(LQueueType *LQ) {
	if (LQ->front == NULL) return 1;
	else return 0;
}

void enQueue(LQueueType *LQ, element item) {
	QNode *newNode = (QNode *)malloc(sizeof(QNode));
	newNode->data = item;
	newNode->link = NULL;
	if (LQ->front == NULL) {
		LQ->front = newNode;
		LQ->rear = newNode;
	}
	else {
		LQ->rear->link = newNode;
		LQ->rear = newNode;
	}
}

element deQueue(LQueueType *LQ) {
	QNode *old = LQ->front;
	element item;
	if (isEmpty(LQ)) return 0;
	else {
		item = old->data;
		LQ->front = LQ->front->link;
		if (LQ->front == NULL)
			LQ->rear = NULL;
		free(old);
		return item;
	}
}  // end Queue Operation

// 배열 a에 있는 n개 원소에 대해 기수 정렬을 수행하는 연산
void radixSort(element a[], int n)
{
	int i, bucket, d, factor = 1;

	// 정렬할 자료의 기수, 즉 RADIX에 따라 열 개의 버킷을 큐로 생성
	LQueueType *Q[RADIX];		// 버킷 큐의 헤드 포인터를 포인터 배열로 선언
	for (bucket = 0; bucket < RADIX; bucket++)
		Q[bucket] = createLinkedQueue();

	// 키값의 자릿수만큼, 즉 두 번 기수 정렬을 반복 수행
	for (d = 0; d < DIGIT; d++)
	{
		for (i = 0; i < n; i++)
			enQueue(Q[(a[i] / factor) % 10], a[i]);

		for (bucket = 0, i = 0; bucket < RADIX; bucket++)
			while (!isEmpty(Q[bucket]))
				a[i++] = deQueue(Q[bucket]);

		printf("\n\n %d 단계 : ", d + 1);

		for (i = 0; i < n; i++) printf(" %d", a[i]);

		factor = factor * 10;
	}
}

/* 결과
<<<<<< 기수 정렬 수행 >>>>>>

1 단계 :  10 30 31 2 22 16 8 69

2 단계 : 2 8 10 16 22 30 31 69
*/