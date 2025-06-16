#include <stdio.h>
#include <stdlib.h>

#define RADIX 10	// ������ �ڷ���� Ű���� 10�����̹Ƿ� RADIX�� 10���� ����
#define DIGIT 2		// ������ �ڷ���� Ű���� �� �ڸ��̹Ƿ� DIGIT�� 2�� ����

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

	printf("\n <<<<<< ��� ���� ���� >>>>>>");
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

// �迭 a�� �ִ� n�� ���ҿ� ���� ��� ������ �����ϴ� ����
void radixSort(element a[], int n)
{
	int i, bucket, d, factor = 1;

	// ������ �ڷ��� ���, �� RADIX�� ���� �� ���� ��Ŷ�� ť�� ����
	LQueueType *Q[RADIX];		// ��Ŷ ť�� ��� �����͸� ������ �迭�� ����
	for (bucket = 0; bucket < RADIX; bucket++)
		Q[bucket] = createLinkedQueue();

	// Ű���� �ڸ�����ŭ, �� �� �� ��� ������ �ݺ� ����
	for (d = 0; d < DIGIT; d++)
	{
		for (i = 0; i < n; i++)
			enQueue(Q[(a[i] / factor) % 10], a[i]);

		for (bucket = 0, i = 0; bucket < RADIX; bucket++)
			while (!isEmpty(Q[bucket]))
				a[i++] = deQueue(Q[bucket]);

		printf("\n\n %d �ܰ� : ", d + 1);

		for (i = 0; i < n; i++) printf(" %d", a[i]);

		factor = factor * 10;
	}
}

/* ���
<<<<<< ��� ���� ���� >>>>>>

1 �ܰ� :  10 30 31 2 22 16 8 69

2 �ܰ� : 2 8 10 16 22 30 31 69
*/